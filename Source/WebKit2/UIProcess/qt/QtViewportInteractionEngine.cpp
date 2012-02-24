/*
 * Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies)
 * Copyright (C) 2011 Benjamin Poulain <benjamin@webkit.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this program; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#include "config.h"
#include "QtViewportInteractionEngine.h"

#include "PassOwnPtr.h"
#include "QtFlickProvider.h"
#include "qquickwebpage_p.h"
#include "qquickwebview_p.h"
#include <QPointF>
#include <QTransform>
#include <QWheelEvent>
#include <QtQuick/qquickitem.h>

namespace WebKit {

static const int kScaleAnimationDurationMillis = 250;

// UPDATE DEFERRING (SUSPEND/RESUME)
// =================================
//
// When interaction with the content, either by animating or by the hand of the user,
// it is important to ensure smooth animations of at least 60fps in order to give a
// good user experience.
//
// In order to do this we need to get rid of unknown factors. These include device
// sensors (geolocation, orientation updates etc), CSS3 animations, JavaScript
// exectution, sub resource loads etc. We do this by emitting suspend and resume
// signals, which are then handled by the viewport and propagates to the right place.
//
// For this reason the ViewportUpdateDeferrer guard must be used when we interact
// or animate the content.
//
// It should be noted that when we update content properties, we might receive notify
// signals send my the content item itself, and care should be taken to not act on
// these unconditionally. An example of this is the pinch zoom, which changes the
// position and will thus result in a QQuickWebPage::geometryChanged() signal getting
// emitted.
//
// If something should only be executed during update deferring, it is possible to
// check for that using ASSERT(m_suspendCount).

class ViewportUpdateDeferrer {
public:
    ViewportUpdateDeferrer(QtViewportInteractionEngine* engine)
        : engine(engine)
    {
        if (engine->m_suspendCount++)
            return;

        emit engine->contentSuspendRequested();
    }

    ~ViewportUpdateDeferrer()
    {
        if (--(engine->m_suspendCount))
            return;

        emit engine->contentResumeRequested();

        // Make sure that tiles all around the viewport will be requested.
        emit engine->contentWasMoved(QPointF());
    }

private:
    QtViewportInteractionEngine* const engine;
};

inline qreal QtViewportInteractionEngine::cssScaleFromItem(qreal itemScale)
{
    return itemScale / m_constraints.devicePixelRatio;
}

inline qreal QtViewportInteractionEngine::itemScaleFromCSS(qreal cssScale)
{
    return cssScale * m_constraints.devicePixelRatio;
}

inline qreal QtViewportInteractionEngine::itemCoordFromCSS(qreal value)
{
    return value * m_constraints.devicePixelRatio;
}

inline QRectF QtViewportInteractionEngine::itemRectFromCSS(const QRectF& cssRect)
{
    QRectF itemRect;

    itemRect.setX(itemCoordFromCSS(cssRect.x()));
    itemRect.setY(itemCoordFromCSS(cssRect.y()));
    itemRect.setWidth(itemCoordFromCSS(cssRect.width()));
    itemRect.setHeight(itemCoordFromCSS(cssRect.height()));

    return itemRect;
}

QtViewportInteractionEngine::QtViewportInteractionEngine(QQuickWebView* viewport, QQuickWebPage* content, QtFlickProvider* flickProvider)
    : m_viewport(viewport)
    , m_content(content)
    , m_flickProvider(flickProvider)
    , m_suspendCount(0)
    , m_hadUserInteraction(false)
    , m_scaleAnimation(new ScaleAnimation(this))
    , m_pinchStartScale(-1)
{
    reset();

    connect(m_content, SIGNAL(widthChanged()), SLOT(itemSizeChanged()), Qt::DirectConnection);
    connect(m_content, SIGNAL(heightChanged()), SLOT(itemSizeChanged()), Qt::DirectConnection);
    connect(m_flickProvider, SIGNAL(movingChanged()), SLOT(flickableMovingStateChanged()), Qt::DirectConnection);

    connect(m_scaleAnimation, SIGNAL(valueChanged(QVariant)),
            SLOT(scaleAnimationValueChanged(QVariant)), Qt::DirectConnection);
    connect(m_scaleAnimation, SIGNAL(stateChanged(QAbstractAnimation::State, QAbstractAnimation::State)),
            SLOT(scaleAnimationStateChanged(QAbstractAnimation::State, QAbstractAnimation::State)), Qt::DirectConnection);
}

QtViewportInteractionEngine::~QtViewportInteractionEngine()
{
}

qreal QtViewportInteractionEngine::innerBoundedCSSScale(qreal cssScale)
{
    return qBound(m_constraints.minimumScale, cssScale, m_constraints.maximumScale);
}

qreal QtViewportInteractionEngine::outerBoundedCSSScale(qreal cssScale)
{
    if (m_constraints.isUserScalable) {
        // Bounded by [0.1, 10.0] like the viewport meta code in WebCore.
        qreal hardMin = qMax<qreal>(0.1, qreal(0.5) * m_constraints.minimumScale);
        qreal hardMax = qMin<qreal>(10, qreal(2.0) * m_constraints.maximumScale);
        return qBound(hardMin, cssScale, hardMax);
    }
    return innerBoundedCSSScale(cssScale);
}

void QtViewportInteractionEngine::setItemRectVisible(const QRectF& itemRect)
{
    if (itemRect.isEmpty())
        return;

    ViewportUpdateDeferrer guard(this);

    qreal itemScale = m_viewport->width() / itemRect.width();

    m_content->setContentsScale(itemScale);

    // To animate the position together with the scale we multiply the position with the current scale
    // and add it to the page position (displacement on the flickable contentItem because of additional items).
    QPointF newPosition(m_content->pos() + (itemRect.topLeft() * itemScale));

    m_flickProvider->setContentPos(newPosition);
}

bool QtViewportInteractionEngine::animateItemRectVisible(const QRectF& itemRect)
{
    QRectF currentItemRectVisible = m_viewport->mapRectToWebContent(m_viewport->boundingRect());
    if (itemRect == currentItemRectVisible)
        return false;

    m_scaleAnimation->setDuration(kScaleAnimationDurationMillis);
    m_scaleAnimation->setEasingCurve(QEasingCurve::OutCubic);

    m_scaleAnimation->setStartValue(currentItemRectVisible);
    m_scaleAnimation->setEndValue(itemRect);

    m_scaleAnimation->start();
    return true;
}

void QtViewportInteractionEngine::flickableMovingStateChanged()
{
    if (m_flickProvider->isMoving()) {
        if (m_scrollUpdateDeferrer)
            return; // We get the isMoving() signal multiple times.
        panMoveStarted();
    } else
        panMoveEnded();
}

void QtViewportInteractionEngine::panMoveStarted()
{
    m_scrollUpdateDeferrer = adoptPtr(new ViewportUpdateDeferrer(this));

    m_lastScrollPosition = m_flickProvider->contentPos();
    connect(m_flickProvider, SIGNAL(contentXChanged()), SLOT(flickableMovingPositionUpdate()));
    connect(m_flickProvider, SIGNAL(contentYChanged()), SLOT(flickableMovingPositionUpdate()));
}

void QtViewportInteractionEngine::panMoveEnded()
{
    // This method is called on the end of the pan or pan kinetic animation.
    m_scrollUpdateDeferrer.clear();

    m_lastScrollPosition = QPointF();
    disconnect(m_flickProvider, SIGNAL(contentXChanged()), this, SLOT(flickableMovingPositionUpdate()));
    disconnect(m_flickProvider, SIGNAL(contentYChanged()), this, SLOT(flickableMovingPositionUpdate()));
}

void QtViewportInteractionEngine::flickableMovingPositionUpdate()
{
    QPointF newPosition = m_flickProvider->contentPos();

    emit contentWasMoved(m_lastScrollPosition - newPosition);

    m_lastScrollPosition = newPosition;
}

void QtViewportInteractionEngine::scaleAnimationStateChanged(QAbstractAnimation::State newState, QAbstractAnimation::State /*oldState*/)
{
    switch (newState) {
    case QAbstractAnimation::Running:
        if (!m_scaleUpdateDeferrer)
            m_scaleUpdateDeferrer = adoptPtr(new ViewportUpdateDeferrer(this));
        break;
    case QAbstractAnimation::Stopped:
        m_scaleUpdateDeferrer.clear();
        break;
    default:
        break;
    }
}

static inline QPointF boundPosition(const QPointF minPosition, const QPointF& position, const QPointF& maxPosition)
{
    return QPointF(qBound(minPosition.x(), position.x(), maxPosition.x()),
                   qBound(minPosition.y(), position.y(), maxPosition.y()));
}

void QtViewportInteractionEngine::wheelEvent(QWheelEvent* ev)
{
    if (scrollAnimationActive() || scaleAnimationActive() || pinchGestureActive())
        return; // Ignore.

    int delta = ev->delta();
    QPointF newPos = -m_content->pos();

    // A delta that is not mod 120 indicates a device that is sending
    // fine-resolution scroll events, so use the delta as number of wheel ticks
    // and number of pixels to scroll. See also webkit.org/b/29601
    bool fullTick = !(delta % 120);

    static const int cDefaultQtScrollStep = 20;
    static const int wheelScrollLines = 3;
    int scrollLines = (fullTick) ? wheelScrollLines * cDefaultQtScrollStep : 1;

    delta = (fullTick) ? delta / 120.0f : delta;
    delta *= scrollLines;

    if (ev->orientation() == Qt::Horizontal)
        newPos.rx() += delta;
    else
        newPos.ry() += delta;

    QRectF endPosRange = computePosRangeForItemAtScale(m_content->contentsScale());

    QPointF currentPosition = m_flickProvider->contentPos();
    QPointF newPosition = -boundPosition(endPosRange.topLeft(), newPos, endPosRange.bottomRight());
    m_flickProvider->setContentPos(newPosition);

    emit contentWasMoved(currentPosition - newPosition);
}

void QtViewportInteractionEngine::pagePositionRequest(const QPoint& pagePosition)
{
    // Ignore the request if suspended. Can only happen due to delay in event delivery.
    if (m_suspendCount)
        return;

    qreal endItemScale = m_content->contentsScale(); // Stay at same scale.

    QRectF endPosRange = computePosRangeForItemAtScale(endItemScale);
    QPointF endPosition = boundPosition(endPosRange.topLeft(), pagePosition * endItemScale, endPosRange.bottomRight());

    QRectF endVisibleContentRect(endPosition / endItemScale, m_viewport->boundingRect().size() / endItemScale);

    setItemRectVisible(endVisibleContentRect);
}

QRectF QtViewportInteractionEngine::computePosRangeForItemAtScale(qreal itemScale) const
{
    const QSizeF contentItemSize = m_content->contentsSize() * itemScale;
    const QSizeF viewportItemSize = m_viewport->boundingRect().size();

    const qreal horizontalRange = contentItemSize.width() - viewportItemSize.width();
    const qreal verticalRange = contentItemSize.height() - viewportItemSize.height();

    return QRectF(QPointF(0, 0), QSizeF(horizontalRange, verticalRange));
}

void QtViewportInteractionEngine::focusEditableArea(const QRectF& caretArea, const QRectF& targetArea)
{
    QRectF endArea = itemRectFromCSS(targetArea);

    qreal endItemScale = itemScaleFromCSS(innerBoundedCSSScale(2.0));
    const QRectF viewportRect = m_viewport->boundingRect();

    qreal x;
    const qreal borderOffset = 10;
    if ((endArea.width() + borderOffset) * endItemScale <= viewportRect.width()) {
        // Center the input field in the middle of the view, if it is smaller than
        // the view at the scale target.
        x = viewportRect.center().x() - endArea.width() * endItemScale / 2.0;
    } else {
        // Ensure that the caret always has borderOffset contents pixels to the right
        // of it, and secondarily (if possible), that the area has borderOffset
        // contents pixels to the left of it.
        qreal caretOffset = itemCoordFromCSS(caretArea.x()) - endArea.x();
        x = qMin(viewportRect.width() - (caretOffset + borderOffset) * endItemScale, borderOffset * endItemScale);
    }

    const QPointF hotspot = QPointF(endArea.x(), endArea.center().y());
    const QPointF viewportHotspot = QPointF(x, /* FIXME: visibleCenter */ viewportRect.center().y());

    QPointF endPosition = hotspot * endItemScale - viewportHotspot;
    QRectF endPosRange = computePosRangeForItemAtScale(endItemScale);

    endPosition = boundPosition(endPosRange.topLeft(), endPosition, endPosRange.bottomRight());

    QRectF endVisibleContentRect(endPosition / endItemScale, viewportRect.size() / endItemScale);

    animateItemRectVisible(endVisibleContentRect);
}

void QtViewportInteractionEngine::zoomToAreaGestureEnded(const QPointF& touchPoint, const QRectF& targetArea)
{
    if (!targetArea.isValid())
        return;

    if (scrollAnimationActive() || scaleAnimationActive())
        return;

    const int margin = 10; // We want at least a little bit or margin.
    QRectF endArea = itemRectFromCSS(targetArea.adjusted(-margin, -margin, margin, margin));

    const QRectF viewportRect = m_viewport->boundingRect();

    qreal targetCSSScale = cssScaleFromItem(viewportRect.size().width() / endArea.size().width());
    qreal endItemScale = itemScaleFromCSS(innerBoundedCSSScale(qMin(targetCSSScale, qreal(2.5))));

    // We want to end up with the target area filling the whole width of the viewport (if possible),
    // and centralized vertically where the user requested zoom. Thus our hotspot is the center of
    // the targetArea x-wise and the requested zoom position, y-wise.
    const QPointF hotspot = QPointF(endArea.center().x(), touchPoint.y() * m_constraints.devicePixelRatio);
    const QPointF viewportHotspot = viewportRect.center();

    QPointF endPosition = hotspot * endItemScale - viewportHotspot;

    QRectF endPosRange = computePosRangeForItemAtScale(endItemScale);
    endPosition = boundPosition(endPosRange.topLeft(), endPosition, endPosRange.bottomRight());

    QRectF endVisibleContentRect(endPosition / endItemScale, viewportRect.size() / endItemScale);

    animateItemRectVisible(endVisibleContentRect);
}

bool QtViewportInteractionEngine::ensureContentWithinViewportBoundary(bool immediate)
{
    ASSERT(m_suspendCount);

    if (scrollAnimationActive() || scaleAnimationActive())
        return false;

    qreal endItemScale = itemScaleFromCSS(innerBoundedCSSScale(currentCSSScale()));

    const QRectF viewportRect = m_viewport->boundingRect();
    QPointF viewportHotspot = viewportRect.center();

    QPointF endPosition = m_viewport->mapToWebContent(viewportHotspot) * endItemScale - viewportHotspot;

    QRectF endPosRange = computePosRangeForItemAtScale(endItemScale);
    endPosition = boundPosition(endPosRange.topLeft(), endPosition, endPosRange.bottomRight());

    QRectF endVisibleContentRect(endPosition / endItemScale, viewportRect.size() / endItemScale);

    if (immediate) {
        setItemRectVisible(endVisibleContentRect);
        return true;
    }
    return !animateItemRectVisible(endVisibleContentRect);
}

void QtViewportInteractionEngine::reset()
{
    ASSERT(!m_suspendCount);

    m_hadUserInteraction = false;

    m_flickProvider->cancelFlick();
    m_scaleAnimation->stop();
    m_scaleUpdateDeferrer.clear();
    m_scrollUpdateDeferrer.clear();
}

void QtViewportInteractionEngine::applyConstraints(const Constraints& constraints)
{
    // We always have to apply the constrains even if they didn't change, as
    // the initial scale might need to be applied.

    ViewportUpdateDeferrer guard(this);

    m_constraints = constraints;

    if (!m_hadUserInteraction) {
        qreal initialScale = innerBoundedCSSScale(m_constraints.initialScale);
        m_content->setContentsScale(itemScaleFromCSS(initialScale));
    }

    // If the web app successively changes the viewport on purpose
    // it wants to be in control and we should disable animations.
    ensureContentWithinViewportBoundary(/* immediate */ true);
}

qreal QtViewportInteractionEngine::currentCSSScale()
{
    return cssScaleFromItem(m_content->contentsScale());
}

bool QtViewportInteractionEngine::scrollAnimationActive() const
{
    return m_flickProvider->isFlicking();
}

bool QtViewportInteractionEngine::panGestureActive() const
{
    return m_flickProvider->isDragging();
}

void QtViewportInteractionEngine::panGestureStarted(const QTouchEvent* event)
{
    m_hadUserInteraction = true;

    ASSERT(event->type() == QEvent::TouchBegin);

    m_flickProvider->handleTouchFlickEvent(const_cast<QTouchEvent*>(event));
    m_lastPinchCenterInViewportCoordinates = event->touchPoints().first().pos();
}

void QtViewportInteractionEngine::panGestureRequestUpdate(const QTouchEvent* event)
{
    ASSERT(event->type() == QEvent::TouchUpdate);

    m_flickProvider->handleTouchFlickEvent(const_cast<QTouchEvent*>(event));
    m_lastPinchCenterInViewportCoordinates = event->touchPoints().first().pos();
}

void QtViewportInteractionEngine::panGestureCancelled()
{
    // Reset the velocity samples of the flickable.
    // This should only be called by the recognizer if we have a recognized
    // pan gesture and receive a touch event with multiple touch points
    // (ie. transition to a pinch gesture) as it does not move the content
    // back inside valid bounds.
    // When the pinch gesture ends, the content is positioned and scaled
    // back to valid boundaries.
    m_flickProvider->cancelFlick();
}

void QtViewportInteractionEngine::panGestureEnded(const QTouchEvent* event)
{
    ASSERT(event->type() == QEvent::TouchEnd);
    m_flickProvider->handleTouchFlickEvent(const_cast<QTouchEvent*>(event));
    m_lastPinchCenterInViewportCoordinates = event->touchPoints().first().pos();
}

bool QtViewportInteractionEngine::scaleAnimationActive() const
{
    return m_scaleAnimation->state() == QAbstractAnimation::Running;
}

void QtViewportInteractionEngine::interruptScaleAnimation()
{
    // This interrupts the scale animation exactly where it is, even if it is out of bounds.
    m_scaleAnimation->stop();
}

bool QtViewportInteractionEngine::pinchGestureActive() const
{
    return m_pinchStartScale > 0;
}

void QtViewportInteractionEngine::pinchGestureStarted(const QPointF& pinchCenterInViewportCoordinates)
{
    ASSERT(!m_suspendCount);

    if (!m_constraints.isUserScalable)
        return;

    m_hadUserInteraction = true;

    m_scaleUpdateDeferrer = adoptPtr(new ViewportUpdateDeferrer(this));

    m_lastPinchCenterInViewportCoordinates = pinchCenterInViewportCoordinates;
    m_pinchStartScale = m_content->contentsScale();

    // Reset the tiling look-ahead vector so that tiles all around the viewport will be requested on pinch-end.
    emit contentWasMoved(QPointF());
}

void QtViewportInteractionEngine::pinchGestureRequestUpdate(const QPointF& pinchCenterInViewportCoordinates, qreal totalScaleFactor)
{
    ASSERT(m_suspendCount);

    if (!m_constraints.isUserScalable)
        return;

    //  Changes of the center position should move the page even if the zoom factor
    //  does not change.
    const qreal cssScale = cssScaleFromItem(m_pinchStartScale * totalScaleFactor);

    // Allow zooming out beyond mimimum scale on pages that do not explicitly disallow it.
    const qreal targetCSSScale = outerBoundedCSSScale(cssScale);

    scaleContent(m_viewport->mapToWebContent(pinchCenterInViewportCoordinates), targetCSSScale);

    const QPointF positionDiff = pinchCenterInViewportCoordinates - m_lastPinchCenterInViewportCoordinates;
    m_lastPinchCenterInViewportCoordinates = pinchCenterInViewportCoordinates;

    m_flickProvider->setContentPos(m_flickProvider->contentPos() - positionDiff);
}

void QtViewportInteractionEngine::pinchGestureEnded()
{
    ASSERT(m_suspendCount);

    if (!m_constraints.isUserScalable)
        return;

    m_pinchStartScale = -1;
    // Clear the update deferrer now if we're in our final position and there won't be any animation to clear it later.
    if (ensureContentWithinViewportBoundary())
        m_scaleUpdateDeferrer.clear();
}

void QtViewportInteractionEngine::itemSizeChanged()
{
    // FIXME: This needs to be done smarter. What happens if it resizes when we were interacting?
    if (m_suspendCount)
        return;

    ViewportUpdateDeferrer guard(this);
    ensureContentWithinViewportBoundary();
}

void QtViewportInteractionEngine::scaleContent(const QPointF& centerInCSSCoordinates, qreal cssScale)
{
    QPointF oldPinchCenterOnViewport = m_viewport->mapFromWebContent(centerInCSSCoordinates);
    m_content->setContentsScale(itemScaleFromCSS(cssScale));
    QPointF newPinchCenterOnViewport = m_viewport->mapFromWebContent(centerInCSSCoordinates);

    m_flickProvider->setContentPos(m_flickProvider->contentPos() + (newPinchCenterOnViewport - oldPinchCenterOnViewport));
}

#include "moc_QtViewportInteractionEngine.cpp"

}

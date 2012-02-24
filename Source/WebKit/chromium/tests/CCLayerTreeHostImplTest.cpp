/*
 * Copyright (C) 2011 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"

#include "cc/CCLayerTreeHostImpl.h"

#include "FakeWebGraphicsContext3D.h"
#include "GraphicsContext3DPrivate.h"
#include "LayerRendererChromium.h"
#include "cc/CCLayerImpl.h"
#include "cc/CCSingleThreadProxy.h"
#include "cc/CCSolidColorDrawQuad.h"
#include <gtest/gtest.h>

using namespace WebCore;
using namespace WebKit;

namespace {

class CCLayerTreeHostImplTest : public testing::Test, public CCLayerTreeHostImplClient {
public:
    CCLayerTreeHostImplTest()
        : m_didRequestCommit(false)
        , m_didRequestRedraw(false)
    {
        CCSettings settings;
        m_hostImpl = CCLayerTreeHostImpl::create(settings, this);
    }

    virtual void onSwapBuffersCompleteOnImplThread() { }
    virtual void setNeedsRedrawOnImplThread() { m_didRequestRedraw = true; }
    virtual void setNeedsCommitOnImplThread() { m_didRequestCommit = true; }
    virtual void postAnimationEventsToMainThreadOnImplThread(PassOwnPtr<CCAnimationEventsVector>) { }

    static void expectClearedScrollDeltasRecursive(CCLayerImpl* layer)
    {
        ASSERT_EQ(layer->scrollDelta(), IntSize());
        for (size_t i = 0; i < layer->children().size(); ++i)
            expectClearedScrollDeltasRecursive(layer->children()[i].get());
    }

    static void expectContains(const CCScrollAndScaleSet& scrollInfo, int id, const IntSize& scrollDelta)
    {
        int timesEncountered = 0;

        for (size_t i = 0; i < scrollInfo.scrolls.size(); ++i) {
            if (scrollInfo.scrolls[i].layerId != id)
                continue;
            EXPECT_EQ(scrollDelta.width(), scrollInfo.scrolls[i].scrollDelta.width());
            EXPECT_EQ(scrollDelta.height(), scrollInfo.scrolls[i].scrollDelta.height());
            timesEncountered++;
        }

        ASSERT_EQ(timesEncountered, 1);
    }

    void setupScrollAndContentsLayers(const IntSize& contentSize)
    {
        RefPtr<CCLayerImpl> root = CCLayerImpl::create(0);
        root->setScrollable(true);
        root->setScrollPosition(IntPoint(0, 0));
        root->setMaxScrollPosition(contentSize);
        RefPtr<CCLayerImpl> contents = CCLayerImpl::create(1);
        contents->setDrawsContent(true);
        contents->setBounds(contentSize);
        contents->setContentBounds(contentSize);
        root->addChild(contents);
        m_hostImpl->setRootLayer(root);
    }

protected:
    PassRefPtr<GraphicsContext3D> createContext()
    {
        return GraphicsContext3DPrivate::createGraphicsContextFromWebContext(adoptPtr(new FakeWebGraphicsContext3D()), GraphicsContext3D::RenderDirectlyToHostWindow);
    }

    DebugScopedSetImplThread m_alwaysImplThread;
    OwnPtr<CCLayerTreeHostImpl> m_hostImpl;
    bool m_didRequestCommit;
    bool m_didRequestRedraw;
};

TEST_F(CCLayerTreeHostImplTest, scrollDeltaNoLayers)
{
    ASSERT_FALSE(m_hostImpl->rootLayer());

    OwnPtr<CCScrollAndScaleSet> scrollInfo = m_hostImpl->processScrollDeltas();
    ASSERT_EQ(scrollInfo->scrolls.size(), 0u);
}

TEST_F(CCLayerTreeHostImplTest, scrollDeltaTreeButNoChanges)
{
    RefPtr<CCLayerImpl> root = CCLayerImpl::create(0);
    root->addChild(CCLayerImpl::create(1));
    root->addChild(CCLayerImpl::create(2));
    root->children()[1]->addChild(CCLayerImpl::create(3));
    root->children()[1]->addChild(CCLayerImpl::create(4));
    root->children()[1]->children()[0]->addChild(CCLayerImpl::create(5));
    m_hostImpl->setRootLayer(root);

    expectClearedScrollDeltasRecursive(root.get());

    OwnPtr<CCScrollAndScaleSet> scrollInfo;

    scrollInfo = m_hostImpl->processScrollDeltas();
    ASSERT_EQ(scrollInfo->scrolls.size(), 0u);
    expectClearedScrollDeltasRecursive(root.get());

    scrollInfo = m_hostImpl->processScrollDeltas();
    ASSERT_EQ(scrollInfo->scrolls.size(), 0u);
    expectClearedScrollDeltasRecursive(root.get());
}

TEST_F(CCLayerTreeHostImplTest, scrollDeltaRepeatedScrolls)
{
    IntPoint scrollPosition(20, 30);
    IntSize scrollDelta(11, -15);
    RefPtr<CCLayerImpl> root = CCLayerImpl::create(10);
    root->setScrollPosition(scrollPosition);
    root->setScrollable(true);
    root->setMaxScrollPosition(IntSize(100, 100));
    root->scrollBy(scrollDelta);
    m_hostImpl->setRootLayer(root);

    OwnPtr<CCScrollAndScaleSet> scrollInfo;

    scrollInfo = m_hostImpl->processScrollDeltas();
    ASSERT_EQ(scrollInfo->scrolls.size(), 1u);
    EXPECT_EQ(root->sentScrollDelta(), scrollDelta);
    expectContains(*scrollInfo, root->id(), scrollDelta);

    IntSize scrollDelta2(-5, 27);
    root->scrollBy(scrollDelta2);
    scrollInfo = m_hostImpl->processScrollDeltas();
    ASSERT_EQ(scrollInfo->scrolls.size(), 1u);
    EXPECT_EQ(root->sentScrollDelta(), scrollDelta + scrollDelta2);
    expectContains(*scrollInfo, root->id(), scrollDelta + scrollDelta2);

    root->scrollBy(IntSize());
    scrollInfo = m_hostImpl->processScrollDeltas();
    EXPECT_EQ(root->sentScrollDelta(), scrollDelta + scrollDelta2);
}

TEST_F(CCLayerTreeHostImplTest, scrollRootCallsCommitAndRedraw)
{
    RefPtr<CCLayerImpl> root = CCLayerImpl::create(0);
    root->setScrollable(true);
    root->setScrollPosition(IntPoint(0, 0));
    root->setMaxScrollPosition(IntSize(100, 100));
    m_hostImpl->setRootLayer(root);
    EXPECT_EQ(m_hostImpl->scrollBegin(IntPoint(0, 0), CCInputHandlerClient::Wheel), CCInputHandlerClient::ScrollStarted);
    m_hostImpl->scrollBy(IntSize(0, 10));
    m_hostImpl->scrollEnd();
    EXPECT_TRUE(m_didRequestRedraw);
    EXPECT_TRUE(m_didRequestCommit);
}

TEST_F(CCLayerTreeHostImplTest, wheelEventHandlers)
{
    RefPtr<CCLayerImpl> root = CCLayerImpl::create(0);
    root->setScrollable(true);
    root->setScrollPosition(IntPoint(0, 0));
    root->setMaxScrollPosition(IntSize(100, 100));
    m_hostImpl->setRootLayer(root);
    root->setHaveWheelEventHandlers(true);
    // With registered event handlers, wheel scrolls have to go to the main thread.
    EXPECT_EQ(m_hostImpl->scrollBegin(IntPoint(0, 0), CCInputHandlerClient::Wheel), CCInputHandlerClient::ScrollFailed);

    // But gesture scrolls can still be handled.
    EXPECT_EQ(m_hostImpl->scrollBegin(IntPoint(0, 0), CCInputHandlerClient::Gesture), CCInputHandlerClient::ScrollStarted);
}

TEST_F(CCLayerTreeHostImplTest, pinchGesture)
{
    setupScrollAndContentsLayers(IntSize(100, 100));
    m_hostImpl->setViewportSize(IntSize(50, 50));

    CCLayerImpl* scrollLayer = m_hostImpl->scrollLayer();
    ASSERT(scrollLayer);

    const float minPageScale = 0.5, maxPageScale = 4;

    // Basic pinch zoom in gesture
    {
        m_hostImpl->setPageScaleFactorAndLimits(1, minPageScale, maxPageScale);
        scrollLayer->setPageScaleDelta(1);
        scrollLayer->setScrollDelta(IntSize());

        float pageScaleDelta = 2;
        m_hostImpl->pinchGestureBegin();
        m_hostImpl->pinchGestureUpdate(pageScaleDelta, IntPoint(50, 50));
        m_hostImpl->pinchGestureEnd();
        EXPECT_TRUE(m_didRequestRedraw);
        EXPECT_TRUE(m_didRequestCommit);

        OwnPtr<CCScrollAndScaleSet> scrollInfo = m_hostImpl->processScrollDeltas();
        EXPECT_EQ(scrollInfo->pageScaleDelta, pageScaleDelta);
    }

    // Zoom-in clamping
    {
        m_hostImpl->setPageScaleFactorAndLimits(1, minPageScale, maxPageScale);
        scrollLayer->setPageScaleDelta(1);
        scrollLayer->setScrollDelta(IntSize());
        float pageScaleDelta = 10;

        m_hostImpl->pinchGestureBegin();
        m_hostImpl->pinchGestureUpdate(pageScaleDelta, IntPoint(50, 50));
        m_hostImpl->pinchGestureEnd();

        OwnPtr<CCScrollAndScaleSet> scrollInfo = m_hostImpl->processScrollDeltas();
        EXPECT_EQ(scrollInfo->pageScaleDelta, maxPageScale);
    }

    // Zoom-out clamping
    {
        m_hostImpl->setPageScaleFactorAndLimits(1, minPageScale, maxPageScale);
        scrollLayer->setPageScaleDelta(1);
        scrollLayer->setScrollDelta(IntSize());
        scrollLayer->setScrollPosition(IntPoint(50, 50));

        float pageScaleDelta = 0.1;
        m_hostImpl->pinchGestureBegin();
        m_hostImpl->pinchGestureUpdate(pageScaleDelta, IntPoint(0, 0));
        m_hostImpl->pinchGestureEnd();

        OwnPtr<CCScrollAndScaleSet> scrollInfo = m_hostImpl->processScrollDeltas();
        EXPECT_EQ(scrollInfo->pageScaleDelta, minPageScale);

        // Pushed to (0,0) via clamping against contents layer size.
        expectContains(*scrollInfo, scrollLayer->id(), IntSize(-50, -50));
    }

    // Two-finger panning
    {
        m_hostImpl->setPageScaleFactorAndLimits(1, minPageScale, maxPageScale);
        scrollLayer->setPageScaleDelta(1);
        scrollLayer->setScrollDelta(IntSize());
        scrollLayer->setScrollPosition(IntPoint(20, 20));

        float pageScaleDelta = 1;
        m_hostImpl->pinchGestureBegin();
        m_hostImpl->pinchGestureUpdate(pageScaleDelta, IntPoint(10, 10));
        m_hostImpl->pinchGestureUpdate(pageScaleDelta, IntPoint(20, 20));
        m_hostImpl->pinchGestureEnd();

        OwnPtr<CCScrollAndScaleSet> scrollInfo = m_hostImpl->processScrollDeltas();
        EXPECT_EQ(scrollInfo->pageScaleDelta, pageScaleDelta);
        expectContains(*scrollInfo, scrollLayer->id(), IntSize(-10, -10));
    }
}

TEST_F(CCLayerTreeHostImplTest, pageScaleAnimation)
{
    setupScrollAndContentsLayers(IntSize(100, 100));
    m_hostImpl->setViewportSize(IntSize(50, 50));

    CCLayerImpl* scrollLayer = m_hostImpl->scrollLayer();
    ASSERT(scrollLayer);

    const float minPageScale = 0.5, maxPageScale = 4;
    const double startTimeMs = 1000;
    const double durationMs = 100;

    // Non-anchor zoom-in
    {
        m_hostImpl->setPageScaleFactorAndLimits(1, minPageScale, maxPageScale);
        scrollLayer->setPageScaleDelta(1);
        scrollLayer->setScrollPosition(IntPoint(50, 50));

        m_hostImpl->startPageScaleAnimation(IntSize(0, 0), false, 2, startTimeMs, durationMs);
        m_hostImpl->animate(startTimeMs + durationMs / 2);
        EXPECT_TRUE(m_didRequestRedraw);
        m_hostImpl->animate(startTimeMs + durationMs);
        EXPECT_TRUE(m_didRequestCommit);

        OwnPtr<CCScrollAndScaleSet> scrollInfo = m_hostImpl->processScrollDeltas();
        EXPECT_EQ(scrollInfo->pageScaleDelta, 2);
        expectContains(*scrollInfo, scrollLayer->id(), IntSize(-50, -50));
    }

    // Anchor zoom-out
    {
        m_hostImpl->setPageScaleFactorAndLimits(1, minPageScale, maxPageScale);
        scrollLayer->setPageScaleDelta(1);
        scrollLayer->setScrollPosition(IntPoint(50, 50));

        m_hostImpl->startPageScaleAnimation(IntSize(25, 25), true, minPageScale, startTimeMs, durationMs);
        m_hostImpl->animate(startTimeMs + durationMs);
        EXPECT_TRUE(m_didRequestRedraw);
        EXPECT_TRUE(m_didRequestCommit);

        OwnPtr<CCScrollAndScaleSet> scrollInfo = m_hostImpl->processScrollDeltas();
        EXPECT_EQ(scrollInfo->pageScaleDelta, minPageScale);
        // Pushed to (0,0) via clamping against contents layer size.
        expectContains(*scrollInfo, scrollLayer->id(), IntSize(-50, -50));
    }
}

class DidDrawCheckLayer : public CCLayerImpl {
public:
    static PassRefPtr<DidDrawCheckLayer> create(int id) { return adoptRef(new DidDrawCheckLayer(id)); }

    virtual void didDraw()
    {
        m_didDrawCalled = true;
    }

    virtual void willDraw(LayerRendererChromium*)
    {
        m_willDrawCalled = true;
    }

    bool didDrawCalled() const { return m_didDrawCalled; }
    bool willDrawCalled() const { return m_willDrawCalled; }

private:
    explicit DidDrawCheckLayer(int id)
        : CCLayerImpl(id)
        , m_didDrawCalled(false)
        , m_willDrawCalled(false)
    {
        setAnchorPoint(FloatPoint(0, 0));
        setBounds(IntSize(10, 10));
        setDrawsContent(true);
    }

    bool m_didDrawCalled;
    bool m_willDrawCalled;
};

TEST_F(CCLayerTreeHostImplTest, didDrawNotCalledOnHiddenLayer)
{
    RefPtr<GraphicsContext3D> context = createContext();
    m_hostImpl->initializeLayerRenderer(context);

    // Ensure visibleLayerRect for root layer is empty
    m_hostImpl->setViewportSize(IntSize(0, 0));

    RefPtr<DidDrawCheckLayer> root = DidDrawCheckLayer::create(0);
    m_hostImpl->setRootLayer(root);

    EXPECT_FALSE(root->willDrawCalled());
    EXPECT_FALSE(root->didDrawCalled());

    m_hostImpl->drawLayers();

    EXPECT_FALSE(root->willDrawCalled());
    EXPECT_FALSE(root->didDrawCalled());

    EXPECT_TRUE(root->visibleLayerRect().isEmpty());

    // Ensure visibleLayerRect for root layer is not empty
    m_hostImpl->setViewportSize(IntSize(10, 10));

    EXPECT_FALSE(root->willDrawCalled());
    EXPECT_FALSE(root->didDrawCalled());

    m_hostImpl->drawLayers();

    EXPECT_TRUE(root->willDrawCalled());
    EXPECT_TRUE(root->didDrawCalled());

    EXPECT_FALSE(root->visibleLayerRect().isEmpty());
}

TEST_F(CCLayerTreeHostImplTest, didDrawCalledOnAllLayers)
{
    RefPtr<GraphicsContext3D> context = createContext();
    m_hostImpl->initializeLayerRenderer(context);
    m_hostImpl->setViewportSize(IntSize(10, 10));

    RefPtr<DidDrawCheckLayer> root = DidDrawCheckLayer::create(0);
    m_hostImpl->setRootLayer(root);

    RefPtr<DidDrawCheckLayer> layer1 = DidDrawCheckLayer::create(1);
    root->addChild(layer1);

    RefPtr<DidDrawCheckLayer> layer2 = DidDrawCheckLayer::create(2);
    layer1->addChild(layer2);

    layer1->setOpacity(0.3);
    layer1->setPreserves3D(false);

    EXPECT_FALSE(root->didDrawCalled());
    EXPECT_FALSE(layer1->didDrawCalled());
    EXPECT_FALSE(layer2->didDrawCalled());

    m_hostImpl->drawLayers();

    EXPECT_TRUE(root->didDrawCalled());
    EXPECT_TRUE(layer1->didDrawCalled());
    EXPECT_TRUE(layer2->didDrawCalled());

    EXPECT_NE(root->renderSurface(), layer1->renderSurface());
    EXPECT_TRUE(!!layer1->renderSurface());
}

class BlendStateTrackerContext: public FakeWebGraphicsContext3D {
public:
    BlendStateTrackerContext() : m_blend(false) { }

    virtual bool initialize(Attributes, WebView*, bool renderDirectlyToWebView) { return true; }

    virtual void enable(WGC3Denum cap)
    {
        if (cap == GraphicsContext3D::BLEND)
            m_blend = true;
    }

    virtual void disable(WGC3Denum cap)
    {
        if (cap == GraphicsContext3D::BLEND)
            m_blend = false;
    }

    bool blend() const { return m_blend; }

private:
    bool m_blend;
};

class BlendStateCheckLayer : public CCLayerImpl {
public:
    static PassRefPtr<BlendStateCheckLayer> create(int id) { return adoptRef(new BlendStateCheckLayer(id)); }

    virtual void appendQuads(CCQuadList& quadList, const CCSharedQuadState* sharedQuadState)
    {
        m_quadsAppended = true;

        Color color = m_opaqueColor ? Color::white : Color(0, 0, 0, 0);
        OwnPtr<CCDrawQuad> testBlendingDrawQuad = CCSolidColorDrawQuad::create(sharedQuadState, IntRect(5, 5, 5, 5), color);
        EXPECT_EQ(m_blend, testBlendingDrawQuad->needsBlending());
        EXPECT_EQ(m_hasRenderSurface, !!renderSurface());
    }

    void setExpectation(bool blend, bool hasRenderSurface)
    {
        m_blend = blend;
        m_hasRenderSurface = hasRenderSurface;
        m_quadsAppended = false;
    }

    bool quadsAppended() const { return m_quadsAppended; }

    void setOpaqueColor(bool opaqueColor) { m_opaqueColor = opaqueColor; }

private:
    explicit BlendStateCheckLayer(int id)
        : CCLayerImpl(id)
        , m_blend(false)
        , m_hasRenderSurface(false)
        , m_quadsAppended(false)
        , m_opaqueColor(true)
    {
        setAnchorPoint(FloatPoint(0, 0));
        setBounds(IntSize(10, 10));
        setDrawsContent(true);
    }

    bool m_blend;
    bool m_hasRenderSurface;
    bool m_quadsAppended;
    bool m_opaqueColor;
};

// https://bugs.webkit.org/show_bug.cgi?id=75783
TEST_F(CCLayerTreeHostImplTest, blendingOffWhenDrawingOpaqueLayers)
{
    RefPtr<GraphicsContext3D> context = createContext();
    m_hostImpl->initializeLayerRenderer(context);
    m_hostImpl->setViewportSize(IntSize(10, 10));

    RefPtr<CCLayerImpl> root = CCLayerImpl::create(0);
    root->setAnchorPoint(FloatPoint(0, 0));
    root->setBounds(IntSize(10, 10));
    root->setDrawsContent(false);
    m_hostImpl->setRootLayer(root);

    RefPtr<BlendStateCheckLayer> layer1 = BlendStateCheckLayer::create(1);
    root->addChild(layer1);

    // Opaque layer, drawn without blending.
    layer1->setOpaque(true);
    layer1->setOpaqueColor(true);
    layer1->setExpectation(false, false);
    m_hostImpl->drawLayers();
    EXPECT_TRUE(layer1->quadsAppended());

    // Layer with translucent content, but solid color is opaque, so drawn without blending.
    layer1->setOpaque(false);
    layer1->setOpaqueColor(true);
    layer1->setExpectation(false, false);
    m_hostImpl->drawLayers();
    EXPECT_TRUE(layer1->quadsAppended());

    // Layer with translucent content and painting, so drawn with blending.
    layer1->setOpaque(false);
    layer1->setOpaqueColor(false);
    layer1->setExpectation(true, false);
    m_hostImpl->drawLayers();
    EXPECT_TRUE(layer1->quadsAppended());

    // Layer with translucent opacity, drawn with blending.
    layer1->setOpaque(true);
    layer1->setOpaqueColor(true);
    layer1->setOpacity(0.5);
    layer1->setExpectation(true, false);
    m_hostImpl->drawLayers();
    EXPECT_TRUE(layer1->quadsAppended());

    // Layer with translucent opacity and painting, drawn with blending.
    layer1->setOpaque(true);
    layer1->setOpaqueColor(false);
    layer1->setOpacity(0.5);
    layer1->setExpectation(true, false);
    m_hostImpl->drawLayers();
    EXPECT_TRUE(layer1->quadsAppended());

    RefPtr<BlendStateCheckLayer> layer2 = BlendStateCheckLayer::create(2);
    layer1->addChild(layer2);

    // 2 opaque layers, drawn without blending.
    layer1->setOpaque(true);
    layer1->setOpaqueColor(true);
    layer1->setOpacity(1);
    layer1->setExpectation(false, false);
    layer2->setOpaque(true);
    layer2->setOpaqueColor(true);
    layer2->setOpacity(1);
    layer2->setExpectation(false, false);
    m_hostImpl->drawLayers();
    EXPECT_TRUE(layer1->quadsAppended());
    EXPECT_TRUE(layer2->quadsAppended());

    // Parent layer with translucent content, drawn with blending.
    // Child layer with opaque content, drawn without blending.
    layer1->setOpaque(false);
    layer1->setOpaqueColor(false);
    layer1->setExpectation(true, false);
    layer2->setExpectation(false, false);
    m_hostImpl->drawLayers();
    EXPECT_TRUE(layer1->quadsAppended());
    EXPECT_TRUE(layer2->quadsAppended());

    // Parent layer with translucent content but opaque painting, drawn without blending.
    // Child layer with opaque content, drawn without blending.
    layer1->setOpaque(false);
    layer1->setOpaqueColor(true);
    layer1->setExpectation(false, false);
    layer2->setExpectation(false, false);
    m_hostImpl->drawLayers();
    EXPECT_TRUE(layer1->quadsAppended());
    EXPECT_TRUE(layer2->quadsAppended());

    // Parent layer with translucent opacity and opaque content. Since it has a
    // drawing child, it's drawn to a render surface which carries the opacity,
    // so it's itself drawn without blending.
    // Child layer with opaque content, drawn without blending (parent surface
    // carries the inherited opacity).
    layer1->setOpaque(true);
    layer1->setOpaqueColor(true);
    layer1->setOpacity(0.5);
    layer1->setExpectation(false, true);
    layer2->setExpectation(false, false);
    m_hostImpl->drawLayers();
    EXPECT_TRUE(layer1->quadsAppended());
    EXPECT_TRUE(layer2->quadsAppended());

    // Draw again, but with child non-opaque, to make sure
    // layer1 not culled.
    layer1->setOpaque(true);
    layer1->setOpaqueColor(true);
    layer1->setOpacity(1);
    layer1->setExpectation(false, false);
    layer2->setOpaque(true);
    layer2->setOpaqueColor(true);
    layer2->setOpacity(0.5);
    layer2->setExpectation(true, false);
    m_hostImpl->drawLayers();
    EXPECT_TRUE(layer1->quadsAppended());
    EXPECT_TRUE(layer2->quadsAppended());

    // A second way of making the child non-opaque.
    layer1->setOpaque(true);
    layer1->setOpacity(1);
    layer1->setExpectation(false, false);
    layer2->setOpaque(false);
    layer2->setOpaqueColor(false);
    layer2->setOpacity(1);
    layer2->setExpectation(true, false);
    m_hostImpl->drawLayers();
    EXPECT_TRUE(layer1->quadsAppended());
    EXPECT_TRUE(layer2->quadsAppended());

    // And when the layer says its not opaque but is painted opaque, it is not blended.
    layer1->setOpaque(true);
    layer1->setOpacity(1);
    layer1->setExpectation(false, false);
    layer2->setOpaque(false);
    layer2->setOpaqueColor(true);
    layer2->setOpacity(1);
    layer2->setExpectation(false, false);
    m_hostImpl->drawLayers();
    EXPECT_TRUE(layer1->quadsAppended());
    EXPECT_TRUE(layer2->quadsAppended());
}

class ReshapeTrackerContext: public FakeWebGraphicsContext3D {
public:
    ReshapeTrackerContext() : m_reshapeCalled(false) { }

    virtual bool initialize(Attributes, WebView*, bool renderDirectlyToWebView) { return true; }

    virtual void reshape(int width, int height)
    {
        m_reshapeCalled = true;
    }

    bool reshapeCalled() const { return m_reshapeCalled; }

private:
    bool m_reshapeCalled;
};

class FakeDrawableCCLayerImpl: public CCLayerImpl {
public:
    explicit FakeDrawableCCLayerImpl(int id) : CCLayerImpl(id) { }
};

// Only reshape when we know we are going to draw. Otherwise, the reshape
// can leave the window at the wrong size if we never draw and the proper
// viewport size is never set.
TEST_F(CCLayerTreeHostImplTest, reshapeNotCalledUntilDraw)
{
    ReshapeTrackerContext* reshapeTracker = new ReshapeTrackerContext();
    RefPtr<GraphicsContext3D> context = GraphicsContext3DPrivate::createGraphicsContextFromWebContext(adoptPtr(reshapeTracker), GraphicsContext3D::RenderDirectlyToHostWindow);
    m_hostImpl->initializeLayerRenderer(context);
    m_hostImpl->setViewportSize(IntSize(10, 10));

    RefPtr<CCLayerImpl> root = adoptRef(new FakeDrawableCCLayerImpl(1));
    root->setAnchorPoint(FloatPoint(0, 0));
    root->setBounds(IntSize(10, 10));
    root->setDrawsContent(true);
    m_hostImpl->setRootLayer(root);
    EXPECT_FALSE(reshapeTracker->reshapeCalled());

    m_hostImpl->drawLayers();
    EXPECT_TRUE(reshapeTracker->reshapeCalled());
}

class PartialSwapTrackerContext : public FakeWebGraphicsContext3D {
public:
    virtual bool initialize(Attributes, WebView*, bool renderDirectlyToWebView) { return true; }

    virtual void postSubBufferCHROMIUM(int x, int y, int width, int height)
    {
        m_partialSwapRect = IntRect(x, y, width, height);
    }

    virtual WebString getString(WGC3Denum name)
    {
        if (name == GraphicsContext3D::EXTENSIONS)
            return WebString("GL_CHROMIUM_post_sub_buffer");

        return WebString();
    }

    IntRect partialSwapRect() const { return m_partialSwapRect; }

private:
    IntRect m_partialSwapRect;
};

// Make sure damage tracking propagates all the way to the graphics context,
// where it should request to swap only the subBuffer that is damaged.
TEST_F(CCLayerTreeHostImplTest, partialSwapReceivesDamageRect)
{
    PartialSwapTrackerContext* partialSwapTracker = new PartialSwapTrackerContext();
    RefPtr<GraphicsContext3D> context = GraphicsContext3DPrivate::createGraphicsContextFromWebContext(adoptPtr(partialSwapTracker), GraphicsContext3D::RenderDirectlyToHostWindow);

    // This test creates its own CCLayerTreeHostImpl, so
    // that we can force partial swap enabled.
    CCSettings settings;
    settings.partialSwapEnabled = true;
    OwnPtr<CCLayerTreeHostImpl> layerTreeHostImpl = CCLayerTreeHostImpl::create(settings, this);
    layerTreeHostImpl->initializeLayerRenderer(context);
    layerTreeHostImpl->setViewportSize(IntSize(500, 500));

    RefPtr<CCLayerImpl> root = adoptRef(new FakeDrawableCCLayerImpl(1));
    RefPtr<CCLayerImpl> child = adoptRef(new FakeDrawableCCLayerImpl(2));
    child->setPosition(FloatPoint(12, 13));
    child->setAnchorPoint(FloatPoint(0, 0));
    child->setBounds(IntSize(14, 15));
    child->setDrawsContent(true);
    root->setAnchorPoint(FloatPoint(0, 0));
    root->setBounds(IntSize(500, 500));
    root->setDrawsContent(true);
    root->addChild(child);
    layerTreeHostImpl->setRootLayer(root);

    // First frame, the entire screen should get swapped.
    layerTreeHostImpl->drawLayers();
    layerTreeHostImpl->swapBuffers();
    IntRect actualSwapRect = partialSwapTracker->partialSwapRect();
    IntRect expectedSwapRect = IntRect(IntPoint::zero(), IntSize(500, 500));
    EXPECT_EQ(expectedSwapRect.x(), actualSwapRect.x());
    EXPECT_EQ(expectedSwapRect.y(), actualSwapRect.y());
    EXPECT_EQ(expectedSwapRect.width(), actualSwapRect.width());
    EXPECT_EQ(expectedSwapRect.height(), actualSwapRect.height());

    // Second frame, only the damaged area should get swapped. Damage should be the union
    // of old and new child rects.
    // expected damage rect: IntRect(IntPoint::zero(), IntSize(26, 28));
    // expected swap rect: vertically flipped, with origin at bottom left corner.
    child->setPosition(FloatPoint(0, 0));
    layerTreeHostImpl->drawLayers();
    layerTreeHostImpl->swapBuffers();
    actualSwapRect = partialSwapTracker->partialSwapRect();
    expectedSwapRect = IntRect(IntPoint(0, 500-28), IntSize(26, 28));
    EXPECT_EQ(expectedSwapRect.x(), actualSwapRect.x());
    EXPECT_EQ(expectedSwapRect.y(), actualSwapRect.y());
    EXPECT_EQ(expectedSwapRect.width(), actualSwapRect.width());
    EXPECT_EQ(expectedSwapRect.height(), actualSwapRect.height());

    // Make sure that partial swap is constrained to the viewport dimensions
    // expected damage rect: IntRect(IntPoint::zero(), IntSize(500, 500));
    // expected swap rect: flipped damage rect, but also clamped to viewport
    layerTreeHostImpl->setViewportSize(IntSize(10, 10));
    root->setOpacity(0.7); // this will damage everything
    layerTreeHostImpl->drawLayers();
    layerTreeHostImpl->swapBuffers();
    actualSwapRect = partialSwapTracker->partialSwapRect();
    expectedSwapRect = IntRect(IntPoint::zero(), IntSize(10, 10));
    EXPECT_EQ(expectedSwapRect.x(), actualSwapRect.x());
    EXPECT_EQ(expectedSwapRect.y(), actualSwapRect.y());
    EXPECT_EQ(expectedSwapRect.width(), actualSwapRect.width());
    EXPECT_EQ(expectedSwapRect.height(), actualSwapRect.height());
}

} // namespace

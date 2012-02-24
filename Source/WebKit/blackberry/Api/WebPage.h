/*
 * Copyright (C) 2009, 2010, 2011, 2012 Research In Motion Limited. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef WebPage_h
#define WebPage_h

#include "ActiveNodeContext.h"
#include "BlackBerryGlobal.h"
#include <BlackBerryPlatformGuardedPointer.h>
#include <BlackBerryPlatformInputEvents.h>
#include <imf/input_data.h>
#include <network/NetworkRequest.h>

struct OpaqueJSContext;
typedef const struct OpaqueJSContext* JSContextRef;

struct OpaqueJSValue;
typedef const struct OpaqueJSValue* JSValueRef;

namespace WebCore {
class ChromeClientBlackBerry;
class EditorClientBlackBerry;
class Element;
class Frame;
class FrameLoaderClientBlackBerry;
class GeolocationControllerClientBlackBerry;
class IconDatabaseClientBlackBerry;
class InspectorClientBlackBerry;
class JavaScriptDebuggerBlackBerry;
class Node;
class RenderObject;
class VisibleSelection;
}

class WebDOMDocument;
class WebDOMNode;
template<typename T> class SharedArray;

namespace BlackBerry {
namespace Platform {
class IntPoint;
class IntRect;
class IntSize;
class KeyboardEvent;
class MouseEvent;
class TouchEvent;
class TouchPoint;
}

namespace WebKit {

class BackingStore;
class BackingStoreClient;
class BackingStorePrivate;
class DumpRenderTreeClient;
class RenderQueue;
class WebPageClient;
class WebPageGroupLoadDeferrer;
class WebPagePrivate;
class WebSettings;

enum JavaScriptDataType { JSUndefined = 0, JSNull, JSBoolean, JSNumber, JSString, JSObject, JSException, JSDataTypeMax };

enum ActivationStateType { ActivationActive, ActivationInactive, ActivationStandby };

enum TargetDetectionStrategy {PointBased, RectBased};

class BLACKBERRY_EXPORT WebPage : public Platform::GuardedPointerBase {
public:
    WebPage(WebPageClient*, const WebString& pageGroupName, const Platform::IntRect&);
    void destroy();

    WebPageClient* client() const;

    void load(const char* url, const char* networkToken, bool isInitial = false);

    void loadExtended(const char* url, const char* networkToken, const char* method, Platform::NetworkRequest::CachePolicy = Platform::NetworkRequest::UseProtocolCachePolicy, const char* data = 0, size_t dataLength = 0, const char* const* headers = 0, size_t headersLength = 0, bool mustHandleInternally = false);

    void loadFile(const char* path, const char* overrideContentType = "");

    void loadString(const char* string, const char* baseURL, const char* contentType = "text/html", const char* failingURL = 0);

    void download(const Platform::NetworkRequest&);

    bool executeJavaScript(const char* script, JavaScriptDataType& returnType, WebString& returnValue);

    // This will execute the script even if in-page JavaScript is disabled.
    bool executeJavaScriptInIsolatedWorld(const char* script, JavaScriptDataType& returnType, WebString& returnValue);

    // Takes a UTF16 encoded script that is used explicitly by the pattern matching code
    bool executeJavaScriptInIsolatedWorld(const std::wstring& script, JavaScriptDataType& returnType, WebString& returnValue);

    void initializeIconDataBase();

    void stopLoading();

    // This will force any unload handlers to run.
    void prepareToDestroy();

    void reload();
    void reloadFromCache();

    WebSettings* settings() const;

    void setVisible(bool);
    bool isVisible() const;

    void setScreenOrientation(int);
    void applyPendingOrientationIfNeeded();

    Platform::IntSize viewportSize() const;
    void setViewportSize(const Platform::IntSize& viewportSize, bool ensureFocusElementVisible = true);

    void resetVirtualViewportOnCommitted(bool reset);
    void setVirtualViewportSize(int width, int height);

    // Used for default layout size unless overridden by web content or by other APIs.
    void setDefaultLayoutSize(int width, int height);

    bool mouseEvent(const Platform::MouseEvent&, bool* wheelDeltaAccepted = 0);

    // Handles native javascript touch events.
    bool touchEvent(const Platform::TouchEvent&);

    // For conversion to mouse events.
    void touchEventCancel();
    void touchEventCancelAndClearFocusedNode();
    bool touchPointAsMouseEvent(const Platform::TouchPoint&);

    // Returns true if the key stroke was handled by WebKit.
    bool keyEvent(const Platform::KeyboardEvent&);

    WebString title() const;
    WebString selectedText() const;
    WebString cutSelectedText();
    void insertText(const WebString&);
    void clearCurrentInputField();

    void cut();
    void copy();
    void paste();

    // Text encoding.
    WebString textEncoding();
    WebString forcedTextEncoding();
    void setForcedTextEncoding(const char*);

    // Scroll position returned is in transformed coordinates.
    Platform::IntPoint scrollPosition() const;
    // Scroll position provided should be in transformed coordinates.
    void setScrollPosition(const Platform::IntPoint&);
    bool scrollBy(const Platform::IntSize&, bool scrollMainFrame = true);
    void notifyInRegionScrollStatusChanged(bool status);
    void setScrollOriginPoint(const Platform::IntPoint&);

    BackingStore* backingStore() const;

    bool zoomToFit();
    bool zoomToOneOne();
    void zoomToInitialScale();
    bool blockZoom(int x, int y);
    void blockZoomAnimationFinished();
    bool isAtInitialZoom() const;
    bool isMaxZoomed() const;
    bool isMinZoomed() const;
    bool pinchZoomAboutPoint(double scale, int x, int y);

    bool isUserScalable() const;
    double currentScale() const;
    double initialScale() const;
    double zoomToFitScale() const;
    void setInitialScale(double);
    double minimumScale() const;
    void setMinimumScale(double);
    double maximumScale() const;
    void setMaximumScale(double);

    void assignFocus(Platform::FocusDirection);

    Platform::IntRect focusNodeRect();

    void setFocused(bool);

    void clearBrowsingData();
    void clearHistory();
    void clearCookies();
    void clearCache();
    void clearLocalStorage();

    void runLayoutTests();

     // Finds and selects the next utf8 string that is a case sensitive
     // match in the web page. It will wrap the web page if it reaches
     // the end. An empty string will result in no match and no selection.
     // Returns true if the string matched and false if not.
    bool findNextString(const char*, bool forward = true);

    // JavaScriptDebugger interface.
    bool enableScriptDebugger();
    bool disableScriptDebugger();

    JSContextRef scriptContext() const;
    JSValueRef windowObject() const;

    void addBreakpoint(const unsigned short* url, unsigned urlLength, int lineNumber, const unsigned short* condition, unsigned conditionLength);
    void updateBreakpoint(const unsigned short* url, unsigned urlLength, int lineNumber, const unsigned short* condition, unsigned conditionLength);
    void removeBreakpoint(const unsigned short* url, unsigned urlLength, int lineNumber);

    bool pauseOnExceptions();
    void setPauseOnExceptions(bool);

    void pauseInDebugger();
    void resumeDebugger();

    void stepOverStatementInDebugger();
    void stepIntoStatementInDebugger();
    void stepOutOfFunctionInDebugger();

    unsigned timeoutForJavaScriptExecution() const;
    void setTimeoutForJavaScriptExecution(unsigned ms);

    void setCaretHighlightStyle(Platform::CaretHighlightStyle);

    // IMF functions.
    bool setBatchEditingActive(bool);
    bool setInputSelection(unsigned start, unsigned end);
    int inputCaretPosition() const;
    bool deleteTextRelativeToCursor(unsigned leftOffset, unsigned rightOffset);
    spannable_string_t* selectedText(int32_t flags);
    spannable_string_t* textBeforeCursor(int32_t length, int32_t flags);
    spannable_string_t* textAfterCursor(int32_t length, int32_t flags);
    extracted_text_t* extractedTextRequest(extracted_text_request_t*, int32_t flags);
    int32_t setComposingRegion(int32_t start, int32_t end);
    int32_t finishComposition();
    int32_t setComposingText(spannable_string_t*, int32_t relativeCursorPosition);
    int32_t commitText(spannable_string_t*, int32_t relativeCursorPosition);

    void spellCheckingEnabled(bool);

    void setSelection(const Platform::IntPoint& startPoint, const Platform::IntPoint& endPoint);
    void setCaretPosition(const Platform::IntPoint&);
    void selectAtPoint(const Platform::IntPoint&);
    void selectionCancelled();
    bool selectionContains(const Platform::IntPoint&);

    void popupListClosed(int size, bool* selecteds);
    void popupListClosed(int index);
    void setDateTimeInput(const WebString& value);
    void setColorInput(const WebString& value);

    void onInputLocaleChanged(bool isRTL);
    static void onNetworkAvailabilityChanged(bool available);
    static void onCertificateStoreLocationSet(const WebString& caPath);

    WebString textHasAttribute(const WebString& query) const;

    ActiveNodeContext activeNodeContext(TargetDetectionStrategy) const;

    typedef intptr_t BackForwardId;
    struct BackForwardEntry {
        WebString url;
        WebString originalUrl;
        WebString title;
        WebString networkToken;
        BackForwardId id;
        bool lastVisitWasHTTPNonGet;
    };

    bool canGoBackOrForward(int delta) const;
    // Returns false if there is no page for the given delta (eg.
    // attempt to go back with -1 when on the first page).
    bool goBackOrForward(int delta);
    void goToBackForwardEntry(BackForwardId);

    int backForwardListLength() const;
    void getBackForwardList(SharedArray<BackForwardEntry>& result, unsigned& resultLength) const;
    void releaseBackForwardEntry(BackForwardId) const;
    void clearBackForwardList(bool keepCurrentPage) const;

    void addVisitedLink(const unsigned short* url, unsigned length);

#if defined(ENABLE_WEBDOM) && ENABLE_WEBDOM
    WebDOMDocument document() const;
    WebDOMNode nodeAtPoint(int x, int y);
    bool getNodeRect(const WebDOMNode&, Platform::IntRect& result);
    bool setNodeFocus(const WebDOMNode&, bool on);
    bool setNodeHovered(const WebDOMNode&, bool on);
    bool nodeHasHover(const WebDOMNode&);
#endif

    bool defersLoading() const;

    bool willFireTimer();

    bool isEnableLocalAccessToAllCookies() const;
    void setEnableLocalAccessToAllCookies(bool);

    void enableWebInspector();
    void disableWebInspector();
    void enablePasswordEcho();
    void disablePasswordEcho();
    void dispatchInspectorMessage(const char* message, int length);
    WebCore::Frame* mainFrame() const;

    // FIXME: Needs API review on this header. See PR #120402.
    void notifyPagePause();
    void notifyPageResume();
    void notifyPageBackground();
    void notifyPageForeground();
    void notifyPageFullScreenAllowed();
    void notifyPageFullScreenExit();
    void notifyDeviceIdleStateChange(bool enterIdle);
    void notifyAppActivationStateChange(ActivationStateType);
    void notifySwipeEvent();
    void notifyScreenPowerStateChanged(bool powered);
    void notifyFullScreenVideoExited(bool done);
    void clearPluginSiteData();
    void setJavaScriptCanAccessClipboard(bool);
    bool isWebGLEnabled() const;
    void setWebGLEnabled(bool);

    void destroyWebPageCompositor();

private:
    ~WebPage();

    friend class WebKit::BackingStore;
    friend class WebKit::BackingStoreClient;
    friend class WebKit::BackingStorePrivate;
    friend class WebKit::RenderQueue;
    friend class WebKit::WebPageGroupLoadDeferrer;
    friend class WebCore::ChromeClientBlackBerry;
    friend class WebCore::FrameLoaderClientBlackBerry;
    WebPagePrivate* d;
};
}
}

#endif // WebPage_h

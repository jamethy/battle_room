
#include "web_app.h"
#include "include/wrapper/cef_message_router.h"

#include <iostream>
#include <thread>

namespace BattleRoom {

/**
 * This class (through the CefApp impl) registers javascript functions with the CEF renderer.
 * When the javascript functions defined by CefMessageRouterConfig are called, it passes through here and
 * on to the SdlCefBrowserClient which manages a CefMessageRouterBrowserSide instance which sends the request
 * to a CefMessageRouterBrowserSide::Handler implementation
 */
    class SdlCefRenderProcessHandler : public CefRenderProcessHandler {
    public:

        // CefRenderProcessHandler methods
        void OnWebKitInitialized() override {
            CefMessageRouterConfig config;
            messageRouterRenderSide = CefMessageRouterRendererSide::Create(config);
        }

        void OnContextCreated(CefRefPtr<CefBrowser> browser,
                              CefRefPtr<CefFrame> frame,
                              CefRefPtr<CefV8Context> context) override {
            messageRouterRenderSide->OnContextCreated(browser, frame, context);
        }

        void OnContextReleased(CefRefPtr<CefBrowser> browser,
                               CefRefPtr<CefFrame> frame,
                               CefRefPtr<CefV8Context> context) override {
            messageRouterRenderSide->OnContextReleased(browser, frame, context);
        }

        bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                      CefProcessId source_process,
                                      CefRefPtr<CefProcessMessage> message) override {
            return messageRouterRenderSide->OnProcessMessageReceived(browser, source_process, message);
        }

    private:

        CefRefPtr<CefMessageRouterRendererSide> messageRouterRenderSide;

        IMPLEMENT_REFCOUNTING(SdlCefRenderProcessHandler);
    };

    class SdlCefBrowserProcessHandler : public CefBrowserProcessHandler {

        void OnScheduleMessagePumpWork(int64 delay_ms) override {
//        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
//        CefDoMessageLoopWork();
        }

        IMPLEMENT_REFCOUNTING(SdlCefBrowserProcessHandler);
    };

    WebApp::WebApp()
            : renderProcessHandler(new SdlCefRenderProcessHandler),
              browserProcessHandler(new SdlCefBrowserProcessHandler)
    {}

    void WebApp::doWebBrowserWork(){
        CefDoMessageLoopWork();
    }

    CefRefPtr<CefRenderProcessHandler> WebApp::GetRenderProcessHandler() {
        return renderProcessHandler;
    }

    CefRefPtr<CefBrowserProcessHandler> WebApp::GetBrowserProcessHandler() {
        return browserProcessHandler;
    }


} //BattleRoom namespace
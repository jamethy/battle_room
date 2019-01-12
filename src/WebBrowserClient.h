//
// Created by james on 8/27/18.
//

#ifndef PROJECT_DEATHBLADE_WEBBROWSERCLIENT_H
#define PROJECT_DEATHBLADE_WEBBROWSERCLIENT_H

#include "include/cef_render_process_handler.h"
#include "include/wrapper/cef_message_router.h"
#include "include/cef_life_span_handler.h"
#include "include/internal/cef_ptr.h"
#include "include/cef_render_handler.h"
#include "include/cef_client.h"

namespace BattleRoom {

/**
 * This class serves two main functions: 1) Manages the messageRouterBrowserSide instance that handles javascript calls
 * and 2) know when it the Cef window has closed
 */
    class WebBrowserClient :
            public CefClient,
            public CefLifeSpanHandler,
            public CefRequestHandler {
    public:

        explicit WebBrowserClient(CefRefPtr<CefRenderHandler> ptr);

        ~WebBrowserClient() override;

        bool closeAllowed() const;

        // CefClient methods
        CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;

        CefRefPtr<CefRenderHandler> GetRenderHandler() override;

        CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() override;

        bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                      CefProcessId source_process,
                                      CefRefPtr<CefProcessMessage> message) override;

        // CefLifeSpanHandler methods.
        void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;

        bool DoClose(CefRefPtr<CefBrowser> browser) override;

        void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

        // CefRequestHandler methods:
        bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
                            CefRefPtr<CefFrame> frame,
                            CefRefPtr<CefRequest> request,
                            bool user_gesture,
                            bool is_redirect) override;

        CefRefPtr<CefResourceHandler> GetResourceHandler(
                CefRefPtr<CefBrowser> browser,
                CefRefPtr<CefFrame> frame,
                CefRefPtr<CefRequest> request) override;

        void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
                                       TerminationStatus status) override;

    private:
        int browser_id;
        bool closing = false;
        CefRefPtr<CefRenderHandler> renderHandler;
        CefRefPtr<CefMessageRouterBrowserSide> messageRouterBrowserSide;
        CefRefPtr<CefContextMenuHandler> contextMenuHandler;
        CefMessageRouterBrowserSide::Handler *sampleMessageHandler;

    IMPLEMENT_REFCOUNTING(WebBrowserClient);

    };
}
#endif //PROJECT_DEATHBLADE_WEBBROWSERCLIENT_H

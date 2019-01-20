#ifndef WEB_APP_H
#define WEB_APP_H

#include "include/cef_app.h"

namespace BattleRoom {

    /**
     * For simply rendering HTML this class and the {@code CefRenderProcessHandler} implementation are unnecessary, but inserting
     * them into the application allows for creation of functions and values in javascript.
     *
     * By default the functions are cefQuery and cefQueryCancel, see {@code CefMessageRouterConfig}
     *
     * The {@code CefApp} implementation is only there to provide access to the {@code CefRenderProcessHandler} implementation
     */
    class WebApp : public CefApp {
    public:

        WebApp();

        void doWebBrowserWork();

        // CefApp methods:
        CefRefPtr <CefRenderProcessHandler> GetRenderProcessHandler() override;

        CefRefPtr <CefBrowserProcessHandler> GetBrowserProcessHandler() override;

    private:
        CefRefPtr <CefRenderProcessHandler> renderProcessHandler;
        CefRefPtr <CefBrowserProcessHandler> browserProcessHandler;
        IMPLEMENT_REFCOUNTING(WebApp);

    }; // WebApp class
} // BattleRoom namespace
#endif //WEB_APP_H

//
// Created by james on 8/27/18.
//

#include "web_browser_client.h"

#include "include/wrapper/cef_helpers.h"
#include "include/cef_parser.h"
#include "web_message_handler.h"

namespace BattleRoom {

/**
 * This class is the last step in receiving function calls from javascript (after SdlCefRenderProcessHandler and
 * WebBrowserClient message router managers).
 */
    class SimpleMessageHandler : public CefMessageRouterBrowserSide::Handler {

    public:

        explicit SimpleMessageHandler(WebMessageHandler *messageHandler) : m_webMessageHandler(messageHandler) {}

        bool OnQuery(CefRefPtr<CefBrowser> browser,
                     CefRefPtr<CefFrame> frame,
                     int64 query_id,
                     const CefString &request,
                     bool persistent,
                     CefRefPtr<Callback> callback) override {
            (void) browser; // unused
            (void) frame; // unused
            (void) query_id; // unused
            (void) persistent; // unused

            if (m_webMessageHandler) {
                auto response = m_webMessageHandler->onMessage(request.ToString());
                if (response.statusCode == WebMessageResponse::SUCCESS_CODE) {
                    callback.get()->Success(CefString(response.message));
                } else {
                    callback.get()->Failure(response.statusCode, CefString(response.message));
                }
            }

            return true;
        }

        void OnQueryCanceled(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             int64 query_id) override {
            (void) browser; // unused
            (void) frame; // unused
            (void) query_id; // unused
        }

    private:
        WebMessageHandler *m_webMessageHandler;
    };

/**
 * Prevents a context menu appearing
 */
    class NoContextMenu : public CefContextMenuHandler {
        void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame,
                                 CefRefPtr<CefContextMenuParams> params,
                                 CefRefPtr<CefMenuModel> model) override {
            (void) browser; // unused
            (void) frame; // unused
            (void) params; // unused
            model->Clear();
        }

    IMPLEMENT_REFCOUNTING(NoContextMenu);
    };

    WebBrowserClient::WebBrowserClient(CefRefPtr<CefRenderHandler> ptr, WebMessageHandler *webMessageHandler) :
            renderHandler(ptr),
            contextMenuHandler(new NoContextMenu),
            sampleMessageHandler(new SimpleMessageHandler(webMessageHandler)) {
    }

    WebBrowserClient::~WebBrowserClient() = default;

    CefRefPtr<CefLifeSpanHandler> WebBrowserClient::GetLifeSpanHandler() {
        return this;
    }

    CefRefPtr<CefRenderHandler> WebBrowserClient::GetRenderHandler() {
        return renderHandler;
    }

    CefRefPtr<CefContextMenuHandler> WebBrowserClient::GetContextMenuHandler() {
        return contextMenuHandler;
    }

// CefLifeSpanHandler methods.
    void WebBrowserClient::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
        CEF_REQUIRE_UI_THREAD();

        browser_id = browser->GetIdentifier();

        if (!messageRouterBrowserSide) {
            // Create the browser-side router for query handling.
            CefMessageRouterConfig config;
            messageRouterBrowserSide = CefMessageRouterBrowserSide::Create(config);

            // Register handlers with the router.
            if (sampleMessageHandler) {
                messageRouterBrowserSide->AddHandler(sampleMessageHandler, false);
            }
        }
    }

    bool WebBrowserClient::DoClose(CefRefPtr<CefBrowser> browser) {
        // Must be executed on the UI thread.
        CEF_REQUIRE_UI_THREAD();

        // Closing the main window requires special handling. See the DoClose()
        // documentation in the CEF header for a detailed description of this
        // process.
        if (browser->GetIdentifier() == browser_id) {
            // Set a flag to indicate that the window close should be allowed.
            closing = true;
        }

        // Allow the close. For windowed browsers this will result in the OS close
        // event being sent.
        return false;
    }

    void WebBrowserClient::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
        messageRouterBrowserSide->OnBeforeClose(browser);

        CEF_REQUIRE_UI_THREAD();
        // Free the router when the last browser is closed.
        messageRouterBrowserSide->RemoveHandler(sampleMessageHandler);
        delete sampleMessageHandler;
        messageRouterBrowserSide = nullptr;
    }

    bool WebBrowserClient::closeAllowed() const {
        return closing;
    }

    bool WebBrowserClient::OnBeforeBrowse(CefRefPtr<CefBrowser> browser,
                                          CefRefPtr<CefFrame> frame,
                                          CefRefPtr<CefRequest> request,
                                          bool user_gesture,
                                          bool is_redirect) {
        (void) request; // unused
        (void) user_gesture; // unused
        (void) is_redirect; // unused

        CEF_REQUIRE_UI_THREAD();

        messageRouterBrowserSide->OnBeforeBrowse(browser, frame);
        return false;
    }

    CefRefPtr<CefResourceHandler> WebBrowserClient::GetResourceHandler(
            CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefRefPtr<CefRequest> request) {
        (void) browser; // unused
        (void) frame; // unused
        (void) request; // unused

        CEF_REQUIRE_IO_THREAD();

//    const std::string& url = request->GetURL();

        // This is a minimal implementation of resource loading. For more complex
        // usage (multiple files, zip archives, custom handlers, etc.) you might want
        // to use CefResourceManager. See the "resource_manager" target for an
        // example implementation.
//    const std::string& resource_path = shared::GetResourcePath(url);
//    if (!resource_path.empty())
//        return shared::GetResourceHandler(resource_path);

        return nullptr;
    }

    void WebBrowserClient::OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser,
                                                     TerminationStatus status) {
        (void) status; // unused

        CEF_REQUIRE_UI_THREAD();

        messageRouterBrowserSide->OnRenderProcessTerminated(browser);
    }

    bool WebBrowserClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                                    CefProcessId source_process,
                                                    CefRefPtr<CefProcessMessage> message) {
        CEF_REQUIRE_UI_THREAD();

        return messageRouterBrowserSide->OnProcessMessageReceived(browser, source_process, message);
    }

    void WebBrowserClient::setWebMessageHandler(WebMessageHandler *webMessageHandler) {
        if (messageRouterBrowserSide) {
            if (sampleMessageHandler) {
                messageRouterBrowserSide->RemoveHandler(sampleMessageHandler);
                delete sampleMessageHandler;
            }
            sampleMessageHandler = new SimpleMessageHandler(webMessageHandler);
            messageRouterBrowserSide->AddHandler(sampleMessageHandler, false);
        } else {
            sampleMessageHandler = new SimpleMessageHandler(webMessageHandler);
        }
    }
} // BattleRoom namespace

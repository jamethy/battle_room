//
// Created by james on 8/27/18.
//

#include "WebBrowserClient.h"

#include "include/wrapper/cef_helpers.h"
#include "include/cef_parser.h"

#include <iostream>

namespace BattleRoom {

/**
 * This class is the last step in receiving function calls from javascript (after SdlCefRenderProcessHandler and
 * WebBrowserClient message router managers).
 */
    class SampleMessageHandler : public CefMessageRouterBrowserSide::Handler {

    public:

        bool OnQuery(CefRefPtr<CefBrowser> browser,
                     CefRefPtr<CefFrame> frame,
                     int64 query_id,
                     const CefString &request,
                     bool persistent,
                     CefRefPtr<Callback> callback) override {

            // could parse "request" here for any information
            // CefRefPtr<CefDictionaryValue> requestValue = CefParseJSON(request, JSON_PARSER_RFC)->GetDictionary();

            CefRefPtr<CefDictionaryValue> result_dict = CefDictionaryValue::Create();
            result_dict->SetInt("count", ++counter);

            CefRefPtr<CefValue> value = CefValue::Create();
            value->SetDictionary(result_dict);
            CefString json = CefWriteJSON(value, JSON_WRITER_DEFAULT);

            callback.get()->Success(json);
            return true;
        }

        void OnQueryCanceled(CefRefPtr<CefBrowser> browser,
                             CefRefPtr<CefFrame> frame,
                             int64 query_id) override {
        }

    private:
        int counter = 0;
    };

/**
 * Prevents a context menu appearing
 */
    class NoContextMenu : public CefContextMenuHandler {
        void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame,
                                 CefRefPtr<CefContextMenuParams> params,
                                 CefRefPtr<CefMenuModel> model) override {
            model->Clear();
        }

    IMPLEMENT_REFCOUNTING(NoContextMenu);
    };

    WebBrowserClient::WebBrowserClient(CefRefPtr<CefRenderHandler> ptr) :
            renderHandler(ptr),
            contextMenuHandler(new NoContextMenu) {
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
            sampleMessageHandler = new SampleMessageHandler();
            messageRouterBrowserSide->AddHandler(sampleMessageHandler, false);
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

        CEF_REQUIRE_UI_THREAD();

        messageRouterBrowserSide->OnBeforeBrowse(browser, frame);
        return false;
    }

    CefRefPtr<CefResourceHandler> WebBrowserClient::GetResourceHandler(
            CefRefPtr<CefBrowser> browser,
            CefRefPtr<CefFrame> frame,
            CefRefPtr<CefRequest> request) {
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

        CEF_REQUIRE_UI_THREAD();

        messageRouterBrowserSide->OnRenderProcessTerminated(browser);
    }

    bool WebBrowserClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                                    CefProcessId source_process,
                                                    CefRefPtr<CefProcessMessage> message) {
        CEF_REQUIRE_UI_THREAD();

        return messageRouterBrowserSide->OnProcessMessageReceived(browser, source_process, message);
    }
} // BattleRoom namespace

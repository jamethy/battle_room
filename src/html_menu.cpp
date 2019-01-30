#include <utility>
#include <thread>

//
// Created by james on 1/19/19.
//

#include "html_menu.h"
#include "logger.h"
#include "file_utils.h"

namespace BattleRoom {

    // in input_to_cef.cpp
    void cefHandleInput(Input input, int x, int y, CefBrowser *browser);


    HtmlMenu::HtmlMenu(TextureManager *textureManager, int windowWidth, int windowHeight,
                       WebMessageHandler *webMessageHandler) : m_isShowing(true) {

        m_webRenderer = new WebRenderer(textureManager, windowWidth, windowHeight);
        m_webBrowserClient = new WebBrowserClient(m_webRenderer, webMessageHandler);
        m_drawableMenu.setTextureKey(m_webRenderer->getTextureKey());
    }

    HtmlMenu::~HtmlMenu() {
        Log::debug("Closing drawable menu");
        if (m_webBrowser) {
            m_webBrowser->GetHost()->CloseBrowser(true);
        }
        int count = 0;
        while (!m_webBrowserClient->closeAllowed() && ++count < 1000) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }


    void HtmlMenu::resize(int width, int height) {
        m_webRenderer->resize(width, height);
        if (m_webBrowser) {
            m_webBrowser->GetHost()->WasResized();
        }
    }

    // TODO bound to be a better way
    void HtmlMenu::navigateTo(const std::string &location) {

        if (m_webBrowser) {
            m_webBrowser->GetHost()->CloseBrowser(true);
        }

        // some browser settings
        CefWindowInfo window_info;
        window_info.SetAsWindowless(kNullWindowHandle);

        CefBrowserSettings browserSettings;
        browserSettings.windowless_frame_rate = 60;
        browserSettings.background_color = 0; // allows for transparency

        std::string url = location;
        if (!startsWith(url, "http")) {
            url = "file://" + getResourcePath() + url;
        }
        Log::debug("Loading url ", url);

        // Create the browser object to interpret the HTML
        m_webBrowser = CefBrowserHost::CreateBrowserSync(window_info,
                                                         m_webBrowserClient,
                                                         url,
                                                         browserSettings,
                                                         nullptr);
    }

    void HtmlMenu::handleInput(Input input, int x, int y) {
        if (m_webBrowser) {
            cefHandleInput(std::move(input), x, y, m_webBrowser.get());
        }
    }

    DrawableMenu HtmlMenu::getDrawableMenu() {
        return m_drawableMenu;
    }

    void HtmlMenu::hide() {
        m_isShowing = false;
        m_webBrowser->GetHost()->WasHidden(true);
    }

    void HtmlMenu::show() {
        m_isShowing = true;
        m_webBrowser->GetHost()->WasHidden(false);
    }

    bool HtmlMenu::isShowing() const {
        return m_isShowing;
    }
} // BattleRoom namespace

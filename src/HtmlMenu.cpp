#include <utility>

//
// Created by james on 1/19/19.
//

#include "HtmlMenu.h"
#include "Logger.h"

namespace BattleRoom {

    // in input_to_cef.cpp
    void cefHandleInput(Input input, int x, int y, CefBrowser *browser);


    HtmlMenu::HtmlMenu(TextureManager *textureManager, int windowWidth, int windowHeight,
                       WebMessageHandler *webMessageHandler) {

        m_webRenderer = new WebRenderer(textureManager, windowWidth, windowHeight);
        m_webBrowserClient = new WebBrowserClient(m_webRenderer, webMessageHandler);

        // some browser settings
        CefWindowInfo window_info;
        window_info.SetAsWindowless(kNullWindowHandle);

        CefBrowserSettings browserSettings;
        browserSettings.windowless_frame_rate = 60;
        browserSettings.background_color = 0; // allows for transparency

        // Create the browser object to interpret the HTML
        std::string htmlFile = "file://" + std::string(SDL_GetBasePath()) + "sdl_cef_html.html";
        Log::debug("Creating menu with dimensions [", windowWidth, ", ", windowHeight, "] of ", htmlFile);
        m_webBrowser = CefBrowserHost::CreateBrowserSync(window_info,
                                                         m_webBrowserClient,
                                                         htmlFile,
                                                         browserSettings,
                                                         nullptr);

        m_drawableMenu.setTextureKey(m_webRenderer->getTextureKey());
    }

    HtmlMenu::~HtmlMenu() {
        Log::debug("Closing drawable menu");
        m_webBrowser->GetHost()->CloseBrowser(false);
    }


    void HtmlMenu::resize(int width, int height) {
        m_webRenderer->resize(width, height);
        m_webBrowser->GetHost()->WasResized();
    }

    void HtmlMenu::handleInput(Input input, int x, int y) {
        cefHandleInput(std::move(input), x, y, m_webBrowser.get());
    }

    DrawableMenu HtmlMenu::getDrawableMenu() {
        return m_drawableMenu;
    }
} // BattleRoom namespace

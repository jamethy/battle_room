//
// Created by james on 1/19/19.
//

#ifndef BATTLE_ROOM_HTML_MENU_H
#define BATTLE_ROOM_HTML_MENU_H

#include "drawable_menu.h"
#include "input.h"
#include "web_browser_client.h"
#include "web_message_handler.h"
#include "web_renderer.h"

namespace BattleRoom {

    class HtmlMenu {
    public:

        HtmlMenu(TextureManager *textureManager, int windowWidth, int windowHeight,
                 WebMessageHandler *webMessageHandler = nullptr);

        ~HtmlMenu();

        void resize(int width, int height);

        void navigateTo(const std::string& location);

        void handleInput(Input input, int x, int y);

        DrawableMenu getDrawableMenu();

    private:

        DrawableMenu m_drawableMenu;

        CefRefPtr<WebRenderer> m_webRenderer;
        CefRefPtr<WebBrowserClient> m_webBrowserClient;
        CefRefPtr<CefBrowser> m_webBrowser;

    }; // HtmlMenu class
} // BattleRoom namespace
#endif //BATTLE_ROOM_HTML_MENU_H

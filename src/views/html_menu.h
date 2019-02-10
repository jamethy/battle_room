//
// Created by james on 1/19/19.
//

#ifndef BATTLE_ROOM_HTML_MENU_H
#define BATTLE_ROOM_HTML_MENU_H

#include "display_window/drawable_menu.h"
#include "application/input.h"
#include "views/web_browser_client.h"
#include "views/web_message_handler.h"
#include "views/web_renderer.h"

namespace BattleRoom {

    class HtmlMenu {
    public:

        HtmlMenu(TextureManager *textureManager, int windowWidth, int windowHeight,
                 WebMessageHandler *webMessageHandler = nullptr);

        ~HtmlMenu();

        void hide();

        void show();

        bool isShowing() const;

        void resize(int width, int height);

        void navigateTo(const std::string& location);

        void handleInput(Input input, int x, int y);

        DrawableMenu getDrawableMenu();

    private:

        bool m_isShowing;

        DrawableMenu m_drawableMenu;

        CefRefPtr<WebRenderer> m_webRenderer;
        CefRefPtr<WebBrowserClient> m_webBrowserClient;
        CefRefPtr<CefBrowser> m_webBrowser;

    }; // HtmlMenu class
} // BattleRoom namespace
#endif //BATTLE_ROOM_HTML_MENU_H

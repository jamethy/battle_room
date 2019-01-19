//
// Created by james on 1/19/19.
//

#ifndef PROJECT_DEATHBLADE_HTMLMENU_H
#define PROJECT_DEATHBLADE_HTMLMENU_H

#include <third_party/cef/cef_binary_3.3396.1777.g636f29b_linux64/include/internal/cef_ptr.h>
#include "WebRenderer.h"
#include "WebBrowserClient.h"
#include "input.h"
#include "drawable_menu.h"
#include "WebMessageHandler.h"

namespace BattleRoom {

    class HtmlMenu {
    public:

        HtmlMenu(TextureManager *textureManager, int windowWidth, int windowHeight,
                 WebMessageHandler *webMessageHandler = nullptr);

        ~HtmlMenu();

        void resize(int width, int height);

        void handleInput(Input input, int x, int y);

        DrawableMenu getDrawableMenu();

    private:

        DrawableMenu m_drawableMenu;

        CefRefPtr<WebRenderer> m_webRenderer;
        CefRefPtr<WebBrowserClient> m_webBrowserClient;
        CefRefPtr<CefBrowser> m_webBrowser;

    }; // HtmlMenu class
} // BattleRoom namespace
#endif //PROJECT_DEATHBLADE_HTMLMENU_H

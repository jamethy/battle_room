//
// Created by james on 8/27/18.
//

#ifndef BATTLE_ROOM_WEBRENDERER_H
#define BATTLE_ROOM_WEBRENDERER_H

#include "SDL.h"
#include "display_window/sdl_texture_manager.h"
#include "display_window/texture_manager.h"

#include "include/cef_render_handler.h"

#include <mutex>

namespace BattleRoom {

/**
 * Provides the link between CEF rendering and SDL rendering. The browser object gets the size of the view from this
 * class and then paints the HTML into a buffer which {@code OnPaint} is used to render it to a texture using SDL.
 *
 * This non-CefRenderHandler functions are used to handle window resizing and the actual copying of the texture to the
 * SDL renderer.
 */
    class WebRenderer : public CefRenderHandler {
    public:

        WebRenderer(TextureManager* textureManager, int initialWidth, int initialHeight);

        ~WebRenderer() override;

        /**
         * Resizes the texture to the new width and height
         * Should call on resizing of window
         *
         * @param width new width
         * @param height new height
         */
        void resize(int width, int height);

        std::string getTextureKey();

        // CefRenderHandler functions
        bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) override;

        void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects,
                     const void *buffer, int w, int h) override;

    private:

        int m_desiredWidth;
        int m_desiredHeight;
        std::string m_textureKey;
        TextureManager* m_textureManager;

    IMPLEMENT_REFCOUNTING(WebRenderer);
    };
}
#endif //BATTLE_ROOM_WEBRENDERER_H

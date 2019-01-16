//
// Created by james on 8/27/18.
//

#include "WebRenderer.h"

#include <iostream>

namespace BattleRoom {

    WebRenderer::WebRenderer(TextureManager* textureManager, int w, int h) : m_textureManager(textureManager) {
        m_textureKey = m_textureManager->createTexture(w, h);
    }

    WebRenderer::~WebRenderer() {
        m_textureManager->deleteTexture(m_textureKey);
    }

    bool WebRenderer::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) {
        (void) browser; // unused

        int width = 0, height = 0;
        m_textureManager->getTextureDimensions(m_textureKey, width, height);
        rect = CefRect(0, 0, width, height);
        return true;
    }

    void WebRenderer::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects,
                              const void *buffer, int w, int h) {
        (void) browser; // unused
        (void) type; // unused
        (void) dirtyRects; // unused

        m_textureManager->writeBufferToTexture(m_textureKey, buffer, w, h);
    }

    void WebRenderer::resize(int w, int h) {
        m_textureManager->resizeTexture(m_textureKey, w, h);
    }
} // BattRoom namespace

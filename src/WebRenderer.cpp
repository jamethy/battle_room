//
// Created by james on 8/27/18.
//

#include "WebRenderer.h"
#include "Logger.h"

#include <iostream>

namespace BattleRoom {

    WebRenderer::WebRenderer(TextureManager *textureManager, int w, int h) :
            m_desiredWidth(w),
            m_desiredHeight(h),
            m_textureManager(textureManager) {
        m_textureKey = m_textureManager->createTexture(w, h);
    }

    WebRenderer::~WebRenderer() {
        m_textureManager->deleteTexture(m_textureKey);
    }

    bool WebRenderer::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) {
        (void) browser; // unused
        rect.width = m_desiredWidth;
        rect.height = m_desiredHeight;
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
        m_desiredWidth = w;
        m_desiredHeight = h;
    }

    std::string WebRenderer::getTextureKey() {
        return m_textureKey;
    }
} // BattRoom namespace

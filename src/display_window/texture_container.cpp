//
// Created by james on 1/13/19.
//

#include "display_window/texture_manager.h"

namespace BattleRoom {
    SDL_Texture *TextureContainer::getSdlTexture() {
        return m_sdlTexture;
    }

    void TextureContainer::setSdlTexture(SDL_Texture *sdlTexture) {
        m_sdlTexture = sdlTexture;
    }

    void TextureContainer::drawingLock() {
        m_drawingMutex.lock();
    }

    void TextureContainer::drawingUnlock() {
        m_drawingMutex.unlock();
    }

    void TextureContainer::paintingLock() {
        m_paintingMutex.lock();
    }

    void TextureContainer::paintingUnlock() {
        m_paintingMutex.unlock();
    }

    TextureContainer::TextureContainer(SDL_Texture *sdlTexture) : m_sdlTexture(sdlTexture) {
    }

    TextureContainer::~TextureContainer() {
        m_drawingMutex.lock();
        m_paintingMutex.lock();
        if (m_sdlTexture) {
            SDL_DestroyTexture(m_sdlTexture);
        }
    }

    std::string TextureContainer::generateKey() {
        static int counter = 0;
        return std::to_string(++counter);
    }

    int TextureContainer::getWidth() {
        return m_width;
    }

    void TextureContainer::setWidth(int width) {
        m_width = width;
    }

    int TextureContainer::getHeight() {
        return m_height;
    }

    void TextureContainer::setHeight(int height) {
        m_height = height;
    }

} // BattleRoom namespace

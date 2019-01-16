
#include "sdl_texture_manager.h"

#include "file_utils.h"
#include "WebRenderer.h"
#include "WebBrowserClient.h"
#include "Logger.h"

#include <iostream>
#include <mutex>

using std::string;

namespace BattleRoom {

// constructors

    SdlTextureManager::SdlTextureManager() = default;

    SdlTextureManager::~SdlTextureManager() {
        clear(); // attempt to clear but should already be clear
    }

    TextureContainer *SdlTextureManager::getTexture(string textureKey) {

        // try to load static if not found
        if (m_textureMap.count(textureKey) == 0) {
            string texture_path = getResourcePath() + "/animations/" + textureKey;
            m_textureMap[textureKey] = new TextureContainer(IMG_LoadTexture(m_renderer, texture_path.c_str()));
        }

        return m_textureMap.at(textureKey);
    }

    void SdlTextureManager::clear() {

        for (auto &texture : m_textureMap) {
            SDL_Texture* sdlTexture = texture.second->getSdlTexture();
            if (sdlTexture) {
                SDL_DestroyTexture(sdlTexture);
            }
        }
        m_textureMap.clear();
    }

// getters and setters

    void SdlTextureManager::setRenderer(SDL_Renderer *renderer) {
        m_renderer = renderer;
    }

    SDL_Renderer *SdlTextureManager::getRenderer() {
        return m_renderer;
    }

    void SdlTextureManager::getTextureDimensions(const std::string &textureKey, int &width, int &height) {
        if (m_textureMap.count(textureKey) > 0) {
            const auto &texture = m_textureMap[textureKey];
            width = texture->getWidth();
            height = texture->getHeight();
        }
    }

    void SdlTextureManager::resizeTexture(const std::string &textureKey, int width, int height) {
        if (m_textureMap.count(textureKey) == 0) {
            Log::error("No texture found to resize ", textureKey);
            return;
        }
        resize(m_textureMap[textureKey], width, height);
    }

    void SdlTextureManager::writeBufferToTexture(const std::string &textureKey, const void *buffer, int w, int h) {
        if (m_textureMap.count(textureKey) == 0) {
            Log::error("No texture found to write to for key ", textureKey);
            return;
        }

        TextureContainer* container = m_textureMap[textureKey];

        if (w != container->getWidth() || h != container->getHeight()) {
            resize(container, w, h);
        }

        unsigned char *texture_data = nullptr;
        int texture_pitch = 0;
        size_t bufferSize = static_cast<size_t>(w) * static_cast<size_t>(h) * 4;

        container->paintingLock();
        SDL_LockTexture(container->getSdlTexture(), nullptr, (void **) &texture_data, &texture_pitch);
        memcpy(texture_data, buffer, bufferSize);
        SDL_UnlockTexture(container->getSdlTexture());
        container->paintingUnlock();
    }

    SDL_Texture* createSDLTexture(SDL_Renderer* renderer, int width, int height) {
        auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        return texture;
    }

    void SdlTextureManager::resize(TextureContainer *container, int width, int height) {

        if (width <= 0 || height <= 0) {
            Log::warn("Width, ", width, ", and height, ", height, ", are bad for texture resize.");
        }

        container->drawingLock();
        container->paintingLock();

        SDL_Texture* texture = container->getSdlTexture();
        if (texture) {
            SDL_DestroyTexture(texture);
        }

        container->setWidth(width);
        container->setHeight(height);

        texture = createSDLTexture(m_renderer, width, height);
        container->setSdlTexture(texture);

        container->drawingUnlock();
        container->paintingUnlock();
    }

    std::string SdlTextureManager::createTexture(int width, int height) {
        if (width <= 0 || height <= 0) {
            Log::warn("Width, ", width, ", and height, ", height, ", are bad for new texture");
        }
        auto container = new TextureContainer(createSDLTexture(m_renderer, width, height));
        container->setWidth(width);
        container->setHeight(height);
        std::string textureKey = TextureContainer::generateKey();
        m_textureMap[textureKey] = container;
        return textureKey;
    }

    void SdlTextureManager::deleteTexture(const std::string &textureKey) {
        if (m_textureMap.count(textureKey) == 0) {
            Log::error("No texture found to delete for key ", textureKey);
            return;
        }

        SDL_Texture* sdlTexture = m_textureMap[textureKey]->getSdlTexture();
        if (sdlTexture) {
            SDL_DestroyTexture(sdlTexture);
        }
        m_textureMap.erase(textureKey);
    }
} // BattleRoom namespace

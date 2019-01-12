
#include "sdl_texture_manager.h"

#include "file_utils.h"

#include <iostream>
#include <mutex>

using std::string;

namespace BattleRoom {

    class SdlTextureManager::StreamingTexture {
    public:

        StreamingTexture(int width, int height, SDL_Renderer* renderer) {
            resize(width, height, renderer);
        }

        ~StreamingTexture() {
            m_drawingMutex.lock();
            m_paintingMutex.lock();
            if (m_texture) {
                SDL_DestroyTexture(m_texture);
            }
        }

        SDL_Texture *getTexture() {
            return m_texture;
        }

        void resize(int w, int h, SDL_Renderer *renderer) {

            m_paintingMutex.lock();
            drawingLock();
            if (m_texture) {
                SDL_DestroyTexture(m_texture);
            }

            m_width = w;
            m_height = h;

            m_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);
            SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);

            m_paintingMutex.unlock();
            drawingUnlock();
        }

        void paint(const void *buffer, int w, int h, SDL_Renderer* renderer) {

            if (w != m_width || h != m_height) {
                resize(w, h, renderer);
            }

            unsigned char *texture_data = nullptr;
            int texture_pitch = 0;
            size_t bufferSize = static_cast<size_t>(w) * static_cast<size_t>(h) * 4;

            m_paintingMutex.lock();
            SDL_LockTexture(m_texture, nullptr, (void **) &texture_data, &texture_pitch);
            memcpy(texture_data, buffer, bufferSize);
            SDL_UnlockTexture(m_texture);
            m_paintingMutex.unlock();
        }

        void drawingLock() {
            m_drawingMutex.lock();
        }

        void drawingUnlock() {
            m_drawingMutex.unlock();
        }

        static std::string generateKey() {
            static int counter = 0;
            return std::to_string(++counter);
        }

    private:
        int m_width;
        int m_height;
        SDL_Texture *m_texture;
        std::mutex m_paintingMutex;
        std::mutex m_drawingMutex;
    };

// constructors

    SdlTextureManager::SdlTextureManager() {}

    SdlTextureManager::~SdlTextureManager() {
        clear(); // attempt to clear but should already be clear
    }

    SdlTextureManager::Texture SdlTextureManager::getTextureForDrawing(string textureKey) {

        Texture texture;
        texture.textureKey = textureKey;

        if (m_streamingTextureMap.count(textureKey) > 0) {
            StreamingTexture *streamingTexture = m_streamingTextureMap[textureKey];
            streamingTexture->drawingLock();

            texture.sdlTexture = streamingTexture->getTexture();
            texture.textureType = StreamingTextureType;

        } else {

            // try to load static if not found
            if (m_textureMap.count(textureKey) == 0) {
                string texture_path = getResourcePath() + "/animations/" + textureKey;
                m_textureMap[textureKey] = IMG_LoadTexture(m_renderer, texture_path.c_str());
            }

            texture.sdlTexture = m_textureMap[textureKey];
            texture.textureType = texture.sdlTexture != nullptr ? StaticTextureType : UnknownTextureType;
        }

        return texture;
    }

    void SdlTextureManager::unlockTexture(SdlTextureManager::Texture &texture) {
        if (texture.textureType == StreamingTextureType) {
            StreamingTexture *streamingTexture = m_streamingTextureMap[texture.textureKey];
            streamingTexture->drawingUnlock();
        }
    }

    void SdlTextureManager::paintOnTexture(std::string textureKey, const void *buffer, int w, int h) {
        if (m_streamingTextureMap.count(textureKey) > 0) {
            m_streamingTextureMap[textureKey]->paint(buffer, w, h, m_renderer);
        }
    }

    std::string SdlTextureManager::createStreamingTexture(int w, int h) {
        std::string key = SdlTextureManager::StreamingTexture::generateKey();
        m_streamingTextureMap[key] = new SdlTextureManager::StreamingTexture(w, h, m_renderer);
        return key;
    }

    void SdlTextureManager::clear() {

        for (auto &texture : m_textureMap) {
            SDL_DestroyTexture(texture.second);
        }
        m_textureMap.clear();

        for (auto& texture : m_streamingTextureMap) {
            delete texture.second;
        }
        m_streamingTextureMap.clear();
    }

// getters and setters

    void SdlTextureManager::setRenderer(SDL_Renderer *renderer) {
        m_renderer = renderer;
    }

    SDL_Renderer *SdlTextureManager::getRenderer() {
        return m_renderer;
    }
} // BattleRoom namespace

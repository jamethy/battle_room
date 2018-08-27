
#include "sdl_texture_manager.h"

#include "file_utils.h"

#include <iostream>

using std::string;

namespace BattleRoom {

// constructors 

    SdlTextureManager::SdlTextureManager() {}

    SdlTextureManager::~SdlTextureManager() {
        clear(); // attempt to clear but should already be clear
    }

    SDL_Texture *SdlTextureManager::getTexture(string texture) {

        //TODO Add error checking
        if (m_textureMap.count(texture) == 0) {
            string texture_path = getResourcePath() + "/animations/" + texture;
            m_textureMap[texture] = IMG_LoadTexture(m_renderer, texture_path.c_str());
        }

        return m_textureMap[texture];
    }

    void SdlTextureManager::clear() {

        for (auto &texture : m_textureMap) {
            SDL_DestroyTexture(texture.second);
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

} // BattleRoom namespace

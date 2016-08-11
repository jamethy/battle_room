
#include "sdl_texture_manager.h"

using std::string;

using Common::px;

namespace Graphics {

SdlTextureManager::~SdlTextureManager() {
    clear(); // attempt to clear but should already be clear
}

void SdlTextureManager::clear() {

    for (auto& texture : m_textureMap) {
        SDL_DestroyTexture(texture.second);
    }
    m_textureMap.clear();
}

void SdlTextureManager::setRenderer(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

bool SdlTextureManager::isTextureAvailable(string texture) {
    return (getTexture(texture) != nullptr);
}

px SdlTextureManager::getTextureWidth(string texture) {

    int width = -1;

    SDL_Texture* txtr = getTexture(texture);

    if (txtr != nullptr) {
        SDL_QueryTexture(txtr, NULL, NULL, &width, NULL);
    }
    return width;
}

px SdlTextureManager::getTextureHeight(string texture) {

    int height = -1;

    SDL_Texture* txtr = getTexture(texture);

    if (txtr != nullptr) {
        SDL_QueryTexture(txtr, NULL, NULL, NULL, &height);
    }
    return height;
}

SDL_Texture* SdlTextureManager::getTexture(string texture) {

    if (m_textureMap.count(texture) == 0) {
        // TODO get texture path?
        string texture_path = texture;
        m_textureMap[texture] = IMG_LoadTexture(m_renderer, texture_path.c_str());
    }

    return m_textureMap[texture];
}

} // Graphics namespace

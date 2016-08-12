
#include "sdl_texture_manager.h"

#include "battle_room/common/file_utils.h"

#include <iostream>

using std::string;

using Common::px;
using Common::ResourceDescriptor;

namespace Graphics {

string getResourcePath() {
    static string resourcePath;
    if (resourcePath.empty()) {
        char *path = SDL_GetBasePath();
        if (path) {
            resourcePath = path;
            SDL_free(path);
        }
        else {
            std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
            return "";
        }
        
		size_t pos = resourcePath.rfind("bin");
		resourcePath = resourcePath.substr(0, pos) + "res/";
	}
    return resourcePath;
}


SdlTextureManager::SdlTextureManager() {
}

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
        string texture_path = getResourcePath() + texture;
        m_textureMap[texture] = IMG_LoadTexture(m_renderer, texture_path.c_str());
    }

    return m_textureMap[texture];
}

} // Graphics namespace

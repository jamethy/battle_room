
#include "sdl_texture_manager.h"
#include "battle_room/engine/graphics/get_resource_path.h"

#include "battle_room/common/file_utils.h"

#include <iostream>

using std::string;

namespace BattleRoom {

// constructors 

SdlTextureManager::SdlTextureManager() 
{ }

SdlTextureManager::~SdlTextureManager() {
    clear(); // attempt to clear but should already be clear
}

void SdlTextureManager::setRenderer(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

SDL_Texture* SdlTextureManager::getTexture(string texture) {

    //TODO Add error checking
    if (m_textureMap.count(texture) == 0) {
        string texture_path = getResourcePath() + texture;
        m_textureMap[texture] = IMG_LoadTexture(m_renderer, texture_path.c_str());
    }

    return m_textureMap[texture];
}

void SdlTextureManager::clear() {

    for (auto& texture : m_textureMap) {
        SDL_DestroyTexture(texture.second);
    }
    m_textureMap.clear();
}

// implementation of getResourcePath from texture_manager.h
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


} // BattleRoom namespace

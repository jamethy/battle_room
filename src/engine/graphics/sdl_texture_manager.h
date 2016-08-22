#ifndef SDL_TEXTURE_MANAGER
#define SDL_TEXTURE_MANAGER

#include "battle_room/engine/graphics/texture_manager.h"

#include "SDL.h"
#include "SDL_image.h"

#include <string>
#include <unordered_map>

namespace BattleRoom {

class SdlTextureManager : public TextureManager {

public:

    // inherited functions
    
    bool isTextureAvailable(std::string texture);

    px getTextureWidth(std::string texture);
    px getTextureHeight(std::string texture);

    void setRenderer(SDL_Renderer* renderer);

    SDL_Texture* getTexture(std::string texture);
    void clear();

    SdlTextureManager();
    ~SdlTextureManager();

private:

    SDL_Renderer* m_renderer;

    std::unordered_map<std::string,SDL_Texture*> m_textureMap;

}; // SdlTextureManager class
} // BattleRoom namespace
#endif // SDL_TEXTURE_MANAGER

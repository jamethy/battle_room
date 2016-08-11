#ifndef SDL_TEXTURE_MANAGER
#define SDL_TEXTURE_MANAGER

#include "battle_room/engine/graphics/texture_manager.h"

#include "SDL.h"
#include "SDL_image.h"

#include <string>
#include <unordered_map>

namespace Graphics {

class SdlTextureManager : public TextureManager {

public:

    // inherited functions
    
    bool isTextureAvailable(std::string texture);

    Common::px getTextureWidth(std::string texture);
    Common::px getTextureHeight(std::string texture);

    void setRenderer(SDL_Renderer* renderer);

    SDL_Texture* getTexture(std::string texture);
    void clear();

    ~SdlTextureManager();

private:

    SDL_Renderer* m_renderer;

    std::unordered_map<std::string,SDL_Texture*> m_textureMap;

}; // SdlTextureManager class
} // Graphics namespace
#endif // SDL_TEXTURE_MANAGER

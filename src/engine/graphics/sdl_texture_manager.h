#ifndef SDL_TEXTURE_MANAGER
#define SDL_TEXTURE_MANAGER

#include "SDL.h"
#include "SDL_image.h"

#include <string>
#include <unordered_map>

namespace BattleRoom {

/**
 * Creates and destroys SDL_Textures
 */
class SdlTextureManager {

public:

    // constructors
    SdlTextureManager();
    ~SdlTextureManager();

    /**
     * \brief Gets the SDL_Texture from the texture key
     * \para textureKey Key to texture (filepath relative to resource directory)
     * \return Pointer to the texture
     */
    SDL_Texture* getTexture(std::string textureKey);

    /**
     * \brief Destroys all the textures that have been loaded
     */
    void clear();

    // setters and getters 

    void setRenderer(SDL_Renderer* renderer);
    SDL_Renderer* getRenderer();


private:

    SDL_Renderer* m_renderer; ///< Renderer used to read textures

    std::unordered_map<std::string,SDL_Texture*> m_textureMap; ///< Container of loaded textures

}; // SdlTextureManager class
} // BattleRoom namespace
#endif // SDL_TEXTURE_MANAGER

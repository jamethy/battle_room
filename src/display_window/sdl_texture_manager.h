#ifndef BATTLE_ROOM_SDL_TEXTURE_MANAGER
#define BATTLE_ROOM_SDL_TEXTURE_MANAGER

#include "SDL.h"
#include "SDL_image.h"
#include "display_window/texture_container.h"
#include "display_window/texture_manager.h"

#include <string>
#include <unordered_map>
#include <mutex>

namespace BattleRoom {

/**
 * Creates and destroys SDL_Textures
 */
    class SdlTextureManager : public TextureManager {

    public:

        // constructors
        SdlTextureManager();

        ~SdlTextureManager();

        /**
         * \brief Gets the SDL_Texture from the texture key
         * \para textureKey Key to texture (filepath relative to resource directory)
         * \return Pointer to the texture
         */
        TextureContainer *getTexture(std::string textureKey);

        // TextureManager functions
        std::string createTexture(int width, int height);
        void deleteTexture(const std::string& textureKey);
        void getTextureDimensions(const std::string &textureKey, int &width, int &height) override;
        void resizeTexture(const std::string &textureKey, int width, int height) override;
        void writeBufferToTexture(const std::string &textureKey, const void *buffer, int width, int height) override;

        /**
         * \brief Destroys all the textures that have been loaded
         */
        void clear();

        // setters and getters

        void setRenderer(SDL_Renderer *renderer);

        SDL_Renderer *getRenderer();

    private:

        void resize(TextureContainer* container, int width, int height);

        SDL_Renderer *m_renderer; ///< Renderer used to read textures
        std::unordered_map<std::string, TextureContainer *> m_textureMap; ///< Container of loaded textures

    }; // SdlTextureManager class
} // BattleRoom namespace
#endif // BATTLE_ROOM_SDL_TEXTURE_MANAGER

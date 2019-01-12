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

        typedef enum {
            UnknownTextureType,
            StaticTextureType,
            StreamingTextureType
        } TextureType;

        typedef struct {
            std::string textureKey;
            TextureType textureType;
            SDL_Texture* sdlTexture;
        } Texture;

        // constructors
        SdlTextureManager();

        ~SdlTextureManager();

        /**
         * \brief Gets the SDL_Texture from the texture key
         * \para textureKey Key to texture (filepath relative to resource directory)
         * \return Pointer to the texture
         */
        Texture getTextureForDrawing(std::string textureKey);

        void unlockTexture(Texture& texture);

        void paintOnTexture(std::string textureKey, const void *buffer, int w, int h);

        std::string createStreamingTexture(int w, int h);

        /**
         * \brief Destroys all the textures that have been loaded
         */
        void clear();

        // setters and getters

        void setRenderer(SDL_Renderer *renderer);

        SDL_Renderer *getRenderer();

    private:

        class StreamingTexture;

        SDL_Renderer *m_renderer; ///< Renderer used to read textures
        std::unordered_map<std::string, SDL_Texture *> m_textureMap; ///< Container of loaded textures
        std::unordered_map<std::string, StreamingTexture *> m_streamingTextureMap; ///< Container of loaded textures

    }; // SdlTextureManager class
} // BattleRoom namespace
#endif // SDL_TEXTURE_MANAGER

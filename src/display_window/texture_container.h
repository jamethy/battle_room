//
// Created by james on 1/13/19.
//

#ifndef BATTLE_ROOM_TEXTURECONTAINER_H
#define BATTLE_ROOM_TEXTURECONTAINER_H

#include <SDL_system.h>
#include <string>
#include <mutex>

namespace BattleRoom {

    /**
     * Container class for SDL Texture
     */
    class TextureContainer {
    public:

        TextureContainer(SDL_Texture* sdlTexture);
        ~TextureContainer();

        void drawingLock();

        void drawingUnlock();

        void paintingLock();

        void paintingUnlock();

        static std::string generateKey();

        // getters and setters
        SDL_Texture *getSdlTexture();
        void setSdlTexture(SDL_Texture *sdlTexture);

        int getWidth();
        void setWidth(int width);
        int getHeight();
        void setHeight(int height);

    private:

        SDL_Texture *m_sdlTexture;
        std::mutex m_paintingMutex;
        std::mutex m_drawingMutex;
        int m_width;
        int m_height;

    }; // TextureContainer class
} // BattleRoom namespace
#endif //BATTLE_ROOM_TEXTURECONTAINER_H

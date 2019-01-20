//
// Created by james on 1/15/19.
//

#ifndef BATTLE_ROOM_TEXTUREMANAGER_H
#define BATTLE_ROOM_TEXTUREMANAGER_H

#include "texture_container.h"

namespace BattleRoom {

    class TextureManager {

    public:

        virtual std::string createTexture(int width, int height) = 0;

        virtual void deleteTexture(const std::string& textureKey) = 0;

        virtual void getTextureDimensions(const std::string &textureKey, int &width, int &height) = 0;

        virtual void resizeTexture(const std::string &textureKey, int width, int height) = 0;

        virtual void writeBufferToTexture(const std::string &textureKey, const void *buffer, int width, int height) = 0;

    }; // TextureManager class
} // BattleRoom namespace
#endif //BATTLE_ROOM_TEXTUREMANAGER_H

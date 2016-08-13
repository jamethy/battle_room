#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

#include "battle_room/common/pixel.h"

#include <string>

namespace BattleRoom {

std::string getResourcePath();

class TextureManager {

public:

    virtual bool isTextureAvailable(std::string texture) = 0;

    virtual px getTextureWidth(std::string texture) = 0;
    virtual px getTextureHeight(std::string texture) = 0;

}; // TextureManager class
} // BattleRoom namespace
#endif // TEXTURE_MANAGER

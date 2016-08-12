#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

#include "battle_room/common/pixel.h"

#include <string>

namespace Graphics {

std::string getResourcePath();

class TextureManager {

public:

    virtual bool isTextureAvailable(std::string texture);

    virtual Common::px getTextureWidth(std::string texture);
    virtual Common::px getTextureHeight(std::string texture);

}; // TextureManager class
} // Graphics namespace
#endif // TEXTURE_MANAGER

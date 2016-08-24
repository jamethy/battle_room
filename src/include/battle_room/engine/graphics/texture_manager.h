#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER

#include "battle_room/common/pixel.h"

#include <string>

namespace BattleRoom {

/*
 * \brief Function that currently relies on SDL that gets the path to
 * the resource directory
 * \TODO find a better place for this
 * \return Full path to the resource directory
 */
std::string getResourcePath();

/**
 * \breif Manages loading the texture files
 * Get this object from the window rendering the textures
 */
class TextureManager {

public:

    /**
     * \brief Attemps to load the texture
     * \param texture Image filename to load (relative to resoure dir)
     * \return True if texture loaded successfully
     */
    virtual bool isTextureAvailable(std::string texture) = 0;

    /**
     * \brief Gets the width in pixels of the texture
     * \param texture Image filename to load (relative to resoure dir)
     * \return Width in pixels of the image
     */
    virtual px getTextureWidth(std::string texture) = 0;

    /**
     * \brief Gets the height in pixels of the texture
     * \param texture Image filename to load (relative to resoure dir)
     * \return Height in pixels of the image
     */
    virtual px getTextureHeight(std::string texture) = 0;

}; // TextureManager class
} // BattleRoom namespace
#endif // TEXTURE_MANAGER

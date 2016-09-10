#ifndef SDL_DRAWABLE_IMAGE_H
#define SDL_DRAWABLE_IMAGE_H

#include "sdl_drawable.h"

namespace BattleRoom {

class SdlDrawableImage : public SdlDrawable {

public:

    // constructors
    SdlDrawableImage();
    ~SdlDrawableImage();

    // setters

    void setSourceRect(SDL_Rect sourceRect);
    void setImageFile(std::string imageFile);

    // inherited

    void draw(SdlTextureManager& textureManager) override;

private:

    SDL_Rect m_sourceRect; ///< Clip of texture for sprite
    std::string m_imageFile; ///< Image sprite file

}; // SdlDrawableImage class
} // BattleRoom namespace
#endif // SDL_DRAWABLE_IMAGE_H


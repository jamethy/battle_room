#include "sdl_drawable_image.h"

#include "battle_room/common/animation_handler.h"

namespace BattleRoom {

    SdlDrawableImage::SdlDrawableImage() {

    }

    SdlDrawableImage::~SdlDrawableImage() {

    }

// setters

    void SdlDrawableImage::setSourceRect(SDL_Rect sourceRect) {
        m_sourceRect = sourceRect;
    }

    void SdlDrawableImage::setImageFile(std::string imageFile) {
        m_imageFile = imageFile;
    }


// inherited

    void SdlDrawableImage::draw(SdlTextureManager &textureManager) {

        if (isInFrame()) {

            // get the texture
            SDL_Texture *texture = textureManager.getTexture(m_imageFile);
            SDL_Rect *sourceRect = &m_sourceRect;
            SDL_Rect destinationRect = getDestinationRect();

            if (texture == NULL) {
                // get missing animation texture
                Animation &missing_animation = AnimationHandler::getAnimation(MISSING_ANIMATION);
                texture = textureManager.getTexture(missing_animation.getImageFile());
                sourceRect = NULL;
            }
            // Draw the image on the screen
            SDL_RenderCopyEx(textureManager.getRenderer(), texture,
                             sourceRect, &destinationRect,
                             toDegrees(getAngle()),
                             NULL, getFlip()
            );
        }
    }

} // namespace BattleRoom

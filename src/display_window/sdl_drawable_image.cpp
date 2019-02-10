#include "display_window/sdl_drawable_image.h"

#include "animation/animation_handler.h"

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
            SDL_Rect *sourceRect = &m_sourceRect;
            SDL_Rect destinationRect = getDestinationRect();

            TextureContainer* texture = textureManager.getTexture(m_imageFile);

            if (texture->getSdlTexture() == nullptr) {
                // get missing animation texture
                Animation &missing_animation = AnimationHandler::getAnimation(MISSING_ANIMATION);
                texture = textureManager.getTexture(missing_animation.getImageFile());
                sourceRect = NULL;
            }

            // Draw the image on the screen
            if (texture->getSdlTexture()) {
                texture->drawingLock();
                SDL_RenderCopyEx(textureManager.getRenderer(), texture->getSdlTexture(),
                                 sourceRect, &destinationRect,
                                 toDegrees(getAngle()),
                                 NULL, getFlip()
                );
                texture->drawingUnlock();
                // TODO try/catch/finally?
            }
        }
    }
} // namespace BattleRoom

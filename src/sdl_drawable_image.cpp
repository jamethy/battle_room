#include "sdl_drawable_image.h"

#include "animation_handler.h"

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

            SdlTextureManager::Texture texture = textureManager.getTextureForDrawing(m_imageFile);

            if (texture.textureType == SdlTextureManager::UnknownTextureType) {
                // get missing animation texture
                Animation &missing_animation = AnimationHandler::getAnimation(MISSING_ANIMATION);
                texture = textureManager.getTextureForDrawing(missing_animation.getImageFile());
                sourceRect = NULL;
            }

            // Draw the image on the screen
            if (texture.sdlTexture) {
                SDL_RenderCopyEx(textureManager.getRenderer(), texture.sdlTexture,
                                 sourceRect, &destinationRect,
                                 toDegrees(getAngle()),
                                 NULL, getFlip()
                );
            }

            textureManager.unlockTexture(texture);
        }
    }

} // namespace BattleRoom

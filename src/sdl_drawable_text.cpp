#include "sdl_drawable_text.h"
#include "sdl_font_manager.h"

namespace BattleRoom {

    SdlDrawableText::SdlDrawableText() {}

    SdlDrawableText::~SdlDrawableText() {}

// setters

    void SdlDrawableText::setColor(SDL_Color color) {
        m_color = color;
    }

    void SdlDrawableText::setFont(std::string font) {
        m_font = font;
    }

    void SdlDrawableText::setFontSize(int fontSize) {
        m_fontSize = fontSize;
    }

    void SdlDrawableText::setText(std::string text) {
        m_text = text;
    }


// inherited

    void SdlDrawableText::draw(SdlTextureManager &textureManager) {

        if (isInFrame()) {

            SDL_Surface *surface = NULL;
            SDL_Texture *texture = NULL;
            SDL_Rect destinationRect = getDestinationRect();

            surface = TTF_RenderText_Solid(
                    SdlFontManager::getFont(m_font, m_fontSize),
                    m_text.c_str(),
                    m_color
            );

            if (surface == NULL) {
                return;
            }

            texture = SDL_CreateTextureFromSurface(textureManager.getRenderer(), surface);
            if (texture == NULL) {
                SDL_FreeSurface(surface);
                return;
            }

            SDL_RenderCopyEx(textureManager.getRenderer(), texture,
                             NULL, &destinationRect,
                             toDegrees(getAngle()),
                             NULL, SDL_FLIP_NONE
            );

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

    }


} // namespace BattleRoom

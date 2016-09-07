#ifndef SDL_DRAWABLE_TEXT_H
#define SDL_DRAWABLE_TEXT_H

#include "sdl_drawable.h"

namespace BattleRoom {

class SdlDrawableText : public SdlDrawable {

public:

    // constructors
    SdlDrawableText();
    ~SdlDrawableText();

    // setters

    void setColor(SDL_Color);
    void setFont(std::string font);
    void setFontSize(int fontSize);
    void setText(std::string text);

    // inherited

    void draw(SdlTextureManager& textureManager) override;

private:

    SDL_Color m_color; ///< Color to draw text
    std::string m_font; ///< Font to draw with (key for FontManager)
    int m_fontSize; ///< Font size to draw text at (only affects aliasing)
    std::string m_text; ///< text to display

}; // SdlDrawableText class
} // BattleRoom namespace
#endif // SDL_DRAWABLE_TEXT_H


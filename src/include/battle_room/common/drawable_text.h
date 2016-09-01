#ifndef DRAWABLE_TEXT_H
#define DRAWABLE_TEXT_H

#include "battle_room/common/resource.h"
#include "battle_room/common/color.h"
#include "battle_room/common/rel_pixel.h"

namespace BattleRoom {

/**
 * Text that has all the information need to draw on the screen
 */
class DrawableText : public Resource {

public:

    // setters and getters

    void setText(std::string text);
    void setFont(std::string font);
    void setFontSize(int fontSize);
    void setColor(Color color);
    void setTopLeft(RelPixel topLeft);
    void setBottomRight(RelPixel bottomRight);

    std::string getText() const;
    std::string getFont() const;
    int getFontSize() const;
    Color getColor() const;
    RelPixel getTopLeft() const;
    RelPixel getBottomRight() const;

    // inherited
    void applySettings(ResourceDescriptor settings);

private:

    std::string m_text; ///< Text to be drawn
    std::string m_font; ///< Path relative to resources
    int m_fontSize; ///< Fontsize
    Color m_color; ///< Color to draw the text
    RelPixel m_topLeft; ///< Top left position of text
    RelPixel m_bottomRight; ///< Bottom right position of text

}; // DrawableText
} // BattleRoom namespace
#endif // DRAWABLE_TEXT_H

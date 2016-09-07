#ifndef DRAWABLE_TEXT_H
#define DRAWABLE_TEXT_H

#include "battle_room/common/resource.h"
#include "battle_room/common/color.h"
#include "battle_room/common/rel_pixel.h"
#include "battle_room/common/vector3d.h"
#include "battle_room/common/quaternion.h"

namespace BattleRoom {

/**
 * Text that has all the information need to draw on the screen
 */
class DrawableText : public Resource {

public:

    // setters and getters

    void setText(std::string text);
    void setFont(std::string font);
    void setColor(Color color);
    void setLocation(Vector3D location);
    void setOrientation(Quaternion orientation);
    void setWidth(meters width);
    void setHeight(meters height);

    std::string getText() const;
    std::string getFont() const;
    Color getColor() const;
    Vector3D getLocation() const;
    Quaternion getOrientation() const;
    meters getWidth() const;
    meters getHeight() const;


    // inherited
    void applySettings(ResourceDescriptor settings);

private:

    std::string m_text; ///< Text to be drawn
    std::string m_font; ///< Path relative to resources
    Color m_color; ///< Color to draw the text
    Vector3D m_location; ///< Location of the text in 3D space
    Quaternion m_orientation; ///< Orientation of the text in 3D space
    meters m_width; ///< Width of text in space
    meters m_height; ///< Height of text in space

}; // DrawableText
} // BattleRoom namespace
#endif // DRAWABLE_TEXT_H

#include "battle_room/common/drawable_text.h"

namespace BattleRoom {

// apply settings

void DrawableText::applySettings(ResourceDescriptor settings) {

    m_color.applySettings( settings.getSubResource("Color"));
    m_location.applySettings( settings.getSubResource("Location") );
    m_orientation.applySettings( settings.getSubResource("Orientation") );

    ResourceDescriptor sub = settings.getSubResource("Text");
    if (isNotEmpty(sub.getKey())) {
        setText(sub.getValue());
    }

    sub = settings.getSubResource("Font");
    if (isNotEmpty(sub.getValue())) {
        setFont(sub.getValue());
    }

    sub = settings.getSubResource("Width");
    if (isNotEmpty(sub.getValue())) {
        m_width = toMeters(sub.getValue());
    }

    sub = settings.getSubResource("Height");
    if (isNotEmpty(sub.getValue())) {
        m_height = toMeters(sub.getValue());
    }

}

// getters and setters

void DrawableText::setText(std::string text) {
    m_text = text;
}

void DrawableText::setFont(std::string font) {
    m_font = font;
}

void DrawableText::setColor(Color color) {
    m_color = color;
}

void DrawableText::setLocation(Vector3D location) {
    m_location = location;
}

void DrawableText::setOrientation(Quaternion orientation) {
    m_orientation = orientation;
}

void DrawableText::setWidth(meters width) {
    m_width = width;
}

void DrawableText::setHeight(meters height) {
    m_height = height;
}


std::string DrawableText::getText() const {
    return m_text;
}

std::string DrawableText::getFont() const {
    return m_font;
}

Color DrawableText::getColor() const {
    return m_color;
}

Vector3D DrawableText::getLocation() const {
     return m_location;
}

Quaternion DrawableText::getOrientation() const {
     return m_orientation;
}

meters DrawableText::getWidth() const {
    return m_width;
}

meters DrawableText::getHeight() const {
     return m_height;
}

} // BattleRoom namespace

#include "battle_room/common/drawable_text.h"

namespace BattleRoom {

// apply settings

void DrawableText::applySettings(ResourceDescriptor settings) {

    ResourceDescriptor sub = settings.getSubResource("Text");
    if (isNotEmpty(sub.getKey())) {
        setText(sub.getValue());
    }

    sub = settings.getSubResource("Font");
    if (isNotEmpty(sub.getKey())) {
        setFont(sub.getValue());
    }

    sub = settings.getSubResource("FontSize");
    if (isNotEmpty(sub.getKey())) {
        setFont(sub.getValue());
    }

    sub = settings.getSubResource("Color");
    if (isNotEmpty(sub.getKey())) {
        m_color.applySettings(sub);
    }

    sub = settings.getSubResource("TopLeft");
    if (isNotEmpty(sub.getKey())) {
        m_topLeft.applySettings(sub);
    }

    sub = settings.getSubResource("BottomRight");
    if (isNotEmpty(sub.getKey())) {
        m_bottomRight.applySettings(sub);
    }

}

// getters and setters

void DrawableText::setText(std::string text) {
    m_text = text;
}

void DrawableText::setFont(std::string font) {
    m_font = font;
}

void DrawableText::setFontSize(int fontSize) {
    m_fontSize = fontSize;
}

void DrawableText::setColor(Color color) {
    m_color = color;
}

void DrawableText::setTopLeft(RelPixel topLeft) {
    m_topLeft = topLeft;
}

void DrawableText::setBottomRight(RelPixel bottomRight) {
    m_bottomRight = bottomRight;
}

std::string DrawableText::getText() const {
    return m_text;
}

std::string DrawableText::getFont() const {
    return m_font;
}

int DrawableText::getFontSize() const {
    return m_fontSize;
}

Color DrawableText::getColor() const {
    return m_color;
}

RelPixel DrawableText::getTopLeft() const {
    return m_topLeft;
}

RelPixel DrawableText::getBottomRight() const {
    return m_bottomRight;
}

} // BattleRoom namespace

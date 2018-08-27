#include "color.h"

namespace BattleRoom {

// apply settings

    void Color::applySettings(ResourceDescriptor settings) {

        std::vector<std::string> values = split(settings.getValue(), ',');
        if (values.size() == 3 || values.size() == 4) {
            setRed(std::stoi(values[0]));
            setGreen(std::stoi(values[1]));
            setBlue(std::stoi(values[2]));
        }
        if (values.size() == 4) {
            setAlpha(std::stoi(values[2]));
        }

        ResourceDescriptor sub = settings.getSubResource("Red");
        if (isNotEmpty(sub.getValue())) {
            setRed(std::stoi(sub.getValue()));
        }

        sub = settings.getSubResource("Green");
        if (isNotEmpty(sub.getValue())) {
            setGreen(std::stoi(sub.getValue()));
        }

        sub = settings.getSubResource("Blue");
        if (isNotEmpty(sub.getValue())) {
            setBlue(std::stoi(sub.getValue()));
        }

        sub = settings.getSubResource("Alpha");
        if (isNotEmpty(sub.getValue())) {
            setAlpha(std::stoi(sub.getValue()));
        }

    }

// constructors

    Color::Color()
            : m_red(0), m_green(0), m_blue(0), m_alpha(255) {}

    Color::Color(int red, int green, int blue)
            : m_red(red), m_green(green), m_blue(blue), m_alpha(255) {}

    Color::Color(int red, int green, int blue, int alpha)
            : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) {}


//getters and setters

    void Color::setRed(int red) {
        if (red > 255) { red = 255; }
        else if (red < 0) { red = 0; }
        m_red = red;
    }

    void Color::setGreen(int green) {
        if (green > 255) { green = 255; }
        else if (green < 0) { green = 0; }
        m_green = green;
    }

    void Color::setBlue(int blue) {
        if (blue > 255) { blue = 255; }
        else if (blue < 0) { blue = 0; }
        m_blue = blue;
    }

    void Color::setAlpha(int alpha) {
        if (alpha > 255) { alpha = 255; }
        else if (alpha < 0) { alpha = 0; }
        m_alpha = alpha;
    }


    int Color::getRed() {
        return m_red;
    }

    int Color::getGreen() {
        return m_green;
    }

    int Color::getBlue() {
        return m_blue;
    }

    int Color::getAlpha() {
        return m_alpha;
    }


// inherited

} // BattleRoom namespace

#ifndef COLOR_H
#define COLOR_H

#include "resource.h"

namespace BattleRoom {

/**
 * \brief Basic color class in RGBA space
 */
    class Color : public Resource {

    public:

        // Constructors
        Color();

        Color(int red, int green, int blue);

        Color(int red, int green, int blue, int alpha);

        //getters and setters
        void setRed(int red);

        void setGreen(int green);

        void setBlue(int blue);

        void setAlpha(int alpha);

        int getRed();

        int getGreen();

        int getBlue();

        int getAlpha();

        // inherited

        void applySettings(ResourceDescriptor settings);

    private:

        int m_red; // Amount of red 0-255
        int m_green; // Amount of green 0-255
        int m_blue; // Amount of blue 0-255
        int m_alpha; // Amount of alpha 0-255

    }; // Color class
} // BattleRoom namespace
#endif // COLOR_H

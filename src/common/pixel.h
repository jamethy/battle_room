#ifndef BATTLE_ROOM_PIXEL_H
#define BATTLE_ROOM_PIXEL_H

#include "common/resource.h"
#include <string>

namespace BattleRoom {

/**
 * Value of pixel distance
 */
    typedef double px;

/*!
 * \brief Pixel coordinates
 * Note the row is the number of pixels from the TOP of the view/image
 * Note the col is the number of pixels from the LEFT of the view/image
 */
    class Pixel : public Resource {

    public:

        // Constructors
        Pixel();

        Pixel(px row, px col);

        /**
         * \brief Returns the rounded column
         * \return Column in integer form
         */
        int getColInt() const;

        /**
         * \brief Returns the rounded row
         * \return Row in integer form
         */
        int getRowInt() const;

        /**
         * \brief Checks if this is in the rectangle of the two pixels
         * \param topLeft Pixel coordinates in the top left
         * \param bottomRight Pixel coordinates in the bottom right
         * \return True if inside pixels
         */
        bool isBetween(Pixel topLeft, Pixel bottomRight);

        // getters and setters

        px getRow() const;

        px getCol() const;

        void setRow(px row);

        void setCol(px col);

        // inherited
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    private:

        px m_row = 0.0;
        px m_col = 0.0;

    }; // Pixel class

/**
 * \brief Parses a string and resturns a pixel count
 * \param s String to parse
 * \return px value found in s
 */
    px toPx(std::string s);

} // namespace BattleRoom
#endif // BATTLE_ROOM_PIXEL_H

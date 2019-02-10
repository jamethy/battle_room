#ifndef BATTLE_ROOM_REL_PIXEL_H
#define BATTLE_ROOM_REL_PIXEL_H

#include "common/resource.h"

#include <string>

namespace BattleRoom {

/**
 * \brief Unit of relative location on a view/image
 */
    typedef double relpx;

/*!
 * Relative pixel coordinates
 * 0 row is the top, 1 row is the bottom, 0.5 row is middle
 * 0 col is the left, 1 col is the right, 0.5 col is middle
 */
    class RelPixel : public Resource {

    public:

        // Constructors
        RelPixel();

        RelPixel(relpx row, relpx col);

        /**
         * \brief Returns the rounded pixel location
         * Essentially viewHeight*getRow()
         * \return Rounded pixel location
         */
        int getRowInt(int viewHeight) const;

        /**
         * \brief Returns the rounded pixel location
         * Essentially viewWidth*getCol()
         * \return Rounded pixel location
         */
        int getColInt(int viewWidth) const;

        // getters and setters

        relpx getRow() const;

        relpx getCol() const;

        void setRow(relpx row);

        void setCol(relpx col);

        // inherited
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    private:

        relpx m_row = 0.0;
        relpx m_col = 0.0;

    }; // RelPixel class

/**
 * \brief Utility function that parses a string and resturns a pixel count
 */
    relpx toRelPx(std::string s);

} // namespace BattleRoom
#endif // BATTLE_ROOM_REL_PIXEL_H

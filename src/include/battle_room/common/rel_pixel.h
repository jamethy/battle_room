#ifndef REL_PIXEL_H
#define REL_PIXEL_H

#include "battle_room/common/resource.h"

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

    /**
     * \brief Checks if pixel in frame (row/col betwen 0-1)
     * \return True if is in frame
     */
    bool isInFrame() const;

    // getters and setters
    void setRow(relpx row);
    void setCol(relpx col);
    relpx getRow() const;
    relpx getCol() const;

    // inherited
    void applySettings(ResourceDescriptor settings) override;

private:

    relpx m_row = 0.0;
    relpx m_col = 0.0;

}; // RelPixel class

/**
 * \brief Utility function that parses a string and resturns a pixel count
 */
relpx toRelPx(std::string s);

} // namespace BattleRoom
#endif // REL_PIXEL_H

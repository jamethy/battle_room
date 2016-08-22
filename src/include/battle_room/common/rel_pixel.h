#ifndef REL_PIXEL_H
#define REL_PIXEL_H

#include <string>

namespace BattleRoom {

typedef double relpx;

/*!
 * This class is relative
 * e.g. 0 row is the top, 1 row is the bottom, 0.5 row is middle
 * e.g. 0 col is the left, 1 col is the right, 0.5 col is middle
 */
class RelPixel {

public:

    RelPixel();
    RelPixel(relpx row, relpx col);

    /*!
     * The row is the number of pixels from the TOP of the image
     */
    void setRow(relpx row);
    relpx getRow() const;

    
    /*!
     * The col (column) is the number of pixels from the LEFT of the image
     */
    void setCol(relpx col);
    relpx getCol() const;

    /*!
     * These functions round and return the row/column to integers
     */
    int getRowInt(int viewWidth) const;
    int getColInt(int viewHeight) const;

private:

    relpx m_row = 0.0;
    relpx m_col = 0.0;

}; // RelPixel class

/**
 * Parses a string and resturns a pixel count
 */
relpx toRelPx(std::string s);

} // namespace BattleRoom
#endif // REL_PIXEL_H

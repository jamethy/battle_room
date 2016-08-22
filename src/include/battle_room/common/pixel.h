#ifndef PIXEL_H
#define PIXEL_H

#include <string>

namespace BattleRoom {

typedef double px;

/*!
 * This class is now relative because I say it is
 * e.g. 0 row is the top, 1 row is the bottom, 0.5 row is middle
 * e.g. 0 col is the left, 1 col is the right, 0.5 col is middle
 */
class Pixel {

public:

    Pixel();
    Pixel(px row, px col);

    /*!
     * The row is the number of pixels from the TOP of the image
     */
    void setRow(px row);
    px getRow() const;

    
    /*!
     * The col (column) is the number of pixels from the LEFT of the image
     */
    void setCol(px col);
    px getCol() const;

    /*!
     * These functions round and return the row/column to integers
     */
    int getRowInt() const;
    int getColInt() const;

private:

    px m_row = 0.0;
    px m_col = 0.0;

}; // Pixel class

/**
 * Parses a string and resturns a pixel count
 */
px toPx(std::string s);

} // namespace BattleRoom
#endif // PIXEL_H

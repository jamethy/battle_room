#ifndef PIXEL_H
#define PIXEL_H

#include "battle_room/common/resource.h"
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

    // getters and setters

    void setRow(px row);
    void setCol(px col);
    px getRow() const;
    px getCol() const;

    // inherited
    void applySettings(ResourceDescriptor settings) override;

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
#endif // PIXEL_H

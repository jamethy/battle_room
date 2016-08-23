#include "battle_room/common/pixel.h"

#include <cmath>
#include <string>

namespace BattleRoom {

// constructors

Pixel::Pixel() {}

Pixel::Pixel(px row, px col)
    : m_row(row), m_col(col) 
{ }

int Pixel::getRowInt() const {
    return (int)std::round(m_row);
}

int Pixel::getColInt() const {
    return (int)std::round(m_col);
}


// getters and setters

void Pixel::setRow(px row) {
    m_row = row;
}

void Pixel::setCol(px col) {
    m_col = col;
}

px Pixel::getRow() const {
    return m_row;
}

px Pixel::getCol() const {
    return m_col;
}

px toPx(std::string s) {
    return stod(s);
}

} // namespace BattleRoom

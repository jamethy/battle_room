#include "battle_room/common/pixel.h"

#include <cmath>
#include <string>

namespace Common {

Pixel::Pixel(px row, px col)
    : m_row(row), m_col(col) 
{ }

void Pixel::setRow(px row) {
    m_row = row;
}

px Pixel::getRow() {
    return m_row;
}

void Pixel::setCol(px col) {
    m_col = col;
}

px Pixel::getCol() {
    return m_col;
}

int Pixel::getRowInt() {
    return (int)std::round(m_row);
}

int Pixel::getColInt() {
    return (int)std::round(m_col);
}

px stopx(std::string s) {
    return stod(s);
}

} // namespace Common

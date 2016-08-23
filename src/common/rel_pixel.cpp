#include "battle_room/common/rel_pixel.h"

#include <cmath>
#include <string>

namespace BattleRoom {

// Constructors

RelPixel::RelPixel() {}

RelPixel::RelPixel(relpx row, relpx col)
    : m_row(row), m_col(col) 
{ }

int RelPixel::getRowInt(int viewHeight) const {
    return (int)std::round(m_row*viewHeight);
}

int RelPixel::getColInt(int viewWidth) const {
    return (int)std::round(m_col*viewWidth);
}

// getters and setters

void RelPixel::setRow(relpx row) {
    m_row = row;
}

void RelPixel::setCol(relpx col) {
    m_col = col;
}

relpx RelPixel::getRow() const {
    return m_row;
}

relpx RelPixel::getCol() const {
    return m_col;
}

relpx toRelPx(std::string s) {
    return stod(s);
}

} // namespace BattleRoom

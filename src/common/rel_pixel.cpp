#include "battle_room/common/rel_pixel.h"

#include <cmath>
#include <string>

namespace BattleRoom {

RelPixel::RelPixel() {}

RelPixel::RelPixel(relpx row, relpx col)
    : m_row(row), m_col(col) 
{ }

void RelPixel::setRow(relpx row) {
    m_row = row;
}

relpx RelPixel::getRow() const {
    return m_row;
}

void RelPixel::setCol(relpx col) {
    m_col = col;
}

relpx RelPixel::getCol() const {
    return m_col;
}

int RelPixel::getRowInt(int viewWidth) const {
    return (int)std::round(m_row*viewWidth);
}

int RelPixel::getColInt(int viewHeight) const {
    return (int)std::round(m_col*viewHeight);
}

relpx toRelPx(std::string s) {
    return stod(s);
}

} // namespace BattleRoom

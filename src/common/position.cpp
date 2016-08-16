#include "battle_room/common/position.h"

namespace BattleRoom {

meters Position::getX() {
    return m_x;
}

void Position::setX(meters x) {
    m_x = x;
}

meters Position::getY() {
    return m_y;
}

void Position::setY(meters y) {
    m_y = y;
}

} // BattleRoom namespace

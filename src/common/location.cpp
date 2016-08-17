#include "battle_room/common/location.h"

namespace BattleRoom {


meters& Location::x() {
    return m_x;
}

meters& Location::y() {
    return m_y;
}

meters& Location::z() {
    return m_z;
}


meters Location::getX() {
    return m_x;
}

meters Location::getY() {
    return m_y;
}

meters Location::getZ() {
    return m_z;
}


void Location::setX(meters x) {
    m_x = x;
}

void Location::setY(meters y) {
    m_y = y;
}

void Location::setZ(meters z) {
    m_z = z;
}

} // BattleRoom namespace

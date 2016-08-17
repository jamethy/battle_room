#include "battle_room/common/position.h"

namespace BattleRoom {


Location& Position::location() {
    return m_location;
}

Orientation& Position::orientation() {
    return m_orientation;
}


Location Position::getLocation() {
    return m_location;
}

Orientation Position::getOrientation() {
    return m_orientation;
}


void Position::setLocation(Location location) {
    m_location = location;
}

void Position::setOrientation(Orientation orientation) {
    m_orientation = orientation;
}

} // BattleRoom namespace

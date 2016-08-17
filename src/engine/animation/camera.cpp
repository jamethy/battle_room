#include "battle_room/engine/animation/camera.h"

namespace BattleRoom {


Position& Camera::position() {
    return m_position;
}

Position Camera::getPosition() {
    return m_position;
}

void Camera::setPosition(Position pos) {
    m_position = pos;
}




} // BattleRoom namespace

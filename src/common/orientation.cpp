
#include "battle_room/common/orientation.h"

namespace BattleRoom {


radians& Orientation::roll() {
    return m_roll;
}

radians& Orientation::pitch() {
    return m_pitch;
}

radians& Orientation::yaw() {
    return m_yaw;
}


radians Orientation::getRoll() {
    return m_roll;
}

radians Orientation::getPitch() {
    return m_pitch;
}

radians Orientation::getYaw() {
    return m_yaw;
}


void Orientation::setRoll(radians roll) {
    m_roll = roll;
}

void Orientation::setPitch(radians pitch) {
    m_pitch = pitch;
}

void Orientation::setYaw(radians yaw) {
    m_yaw = yaw;
}

}// BattleRoom namespace

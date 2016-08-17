
#include "battle_room/common/orientation.h"

namespace BattleRoom {

void Orientation::setTheta(radians theta) {
    m_theta = theta;
}

radians Orientation::getTheta() {
    return m_theta;
}

}// BattleRoom namespace

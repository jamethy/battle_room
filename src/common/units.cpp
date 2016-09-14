#include "battle_room/common/units.h"

namespace BattleRoom {


seconds toSeconds(std::string str) {
    return stod(str);
}

meters toMeters(std::string str) {
    return stod(str);
}

radians toRadians(std::string str) {
    return stod(str);
}

double toDegrees(radians angle) {
    return angle*180.0/3.14159265359;
}


} // BattleRoom namespace

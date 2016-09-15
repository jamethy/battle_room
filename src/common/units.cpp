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

degrees toDegrees(std::string str) {
    return stod(str);
}

degrees toDegrees(radians angle) {
    return angle*180.0/3.14159265359;
}

radians toRadians(degrees angle) {
    return angle*3.14159265359/180.0;
}


} // BattleRoom namespace

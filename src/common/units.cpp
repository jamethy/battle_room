#include "common/units.h"
#include <cmath>

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

    kilograms toKilograms(std::string str) {
        return stod(str);
    }

    degrees toDegrees(radians angle) {
        return angle * 180.0 / 3.14159265359;
    }

    radians toRadians(degrees angle) {
        return angle * 3.14159265359 / 180.0;
    }

    radians underPi(radians angle) {
        angle = fmod(angle, 2*PI);
        if (angle < -PI) {
            angle += 2*PI;
        } else if (angle > PI) {
            angle -= 2*PI;
        }
        return angle;
    }

    degrees under180(degrees angle) {
        angle = fmod(angle, 360);
        if (angle < -180) {
            angle += 360;
        } else if (angle > 180) {
            angle -= 360;
        }
        return angle;
    }


} // BattleRoom namespace

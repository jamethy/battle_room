#include "battle_room/common/position.h"

namespace BattleRoom {

// Reference Acessors

Vector3D& Position::location() {
    return m_location;
}

Quaternion& Position::orientation() {
    return m_orientation;
}

// setters and getters

Vector3D Position::getLocation() {
    return m_location;
}

Quaternion Position::getOrientation() {
    return m_orientation;
}


void Position::setLocation(Vector3D location) {
    m_location = location;
}

void Position::setOrientation(Quaternion orientation) {
    m_orientation = orientation;
}

void Position::applySettings(ResourceDescriptor settings) {

    ResourceDescriptor sub = settings.getSubResource("Location");
    if (!sub.getKey().empty()) {
        m_location.applySettings(sub);
    } 

    sub = settings.getSubResource("Orientation");
    if (!sub.getKey().empty()) {
        m_orientation.applySettings(sub);
    } 
}

radians toRadians(std::string str) {
    return stod(str);
}

} // BattleRoom namespace

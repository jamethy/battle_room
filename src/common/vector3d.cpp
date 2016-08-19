#include "battle_room/common/vector3d.h"

using std::string;

namespace BattleRoom {

meters& Vector3D::x() {
    return m_x;
}

meters& Vector3D::y() {
    return m_y;
}

meters& Vector3D::z() {
    return m_z;
}

void Vector3D::applySettings(ResourceDescriptor settings) {

    ResourceDescriptor sub = settings.getSubResource("X");
    if (!sub.getKey().empty()) {
        m_x = toMeters(sub.getValue());
    } 

    sub = settings.getSubResource("Y");
    if (!sub.getKey().empty()) {
        m_y = toMeters(sub.getValue());
    } 

    sub = settings.getSubResource("Z");
    if (!sub.getKey().empty()) {
        m_z = toMeters(sub.getValue());
    } 
}

meters toMeters(string str) {
    return stod(str);
}

} // BattleRoom namespace

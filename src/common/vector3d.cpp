#include "battle_room/common/vector3d.h"
#include "battle_room/common/string_utils.h"

#include <cmath>

using std::string;

namespace BattleRoom {

// apply settings

void Vector3D::applySettings(ResourceDescriptor settings) {

    std::vector<string> values = split(settings.getValue(), ',');
    if (values.size() == 3) {
        m_x = toMeters(values[0]);
        m_y = toMeters(values[1]);
        m_z = toMeters(values[2]);
    }

    ResourceDescriptor sub = settings.getSubResource("X");
    if (isNotEmpty(sub.getKey())) {
        m_x = toMeters(sub.getValue());
    } 

    sub = settings.getSubResource("Y");
    if (isNotEmpty(sub.getKey())) {
        m_y = toMeters(sub.getValue());
    } 

    sub = settings.getSubResource("Z");
    if (isNotEmpty(sub.getKey())) {
        m_z = toMeters(sub.getValue());
    } 
}

// constructors

Vector3D::Vector3D() 
    : m_x(0.0), m_y(0.0), m_z(0.0)
{ }

Vector3D::Vector3D(meters x, meters y, meters z)
    : m_x(x), m_y(y), m_z(z)
{ }

// Access by reference

meters& Vector3D::x() {
    return m_x;
}

meters& Vector3D::y() {
    return m_y;
}

meters& Vector3D::z() {
    return m_z;
}

// math functions

meters Vector3D::dot(Vector3D b) const {
    return m_x*b.x() + m_y*b.y() + m_z*b.z();
}

Vector3D Vector3D::cross(Vector3D b) const {
    meters x = m_y*b.z() - m_z*b.y();
    meters y = m_z*b.x() - m_x*b.z();
    meters z = m_x*b.y() - m_y*b.x();
    return Vector3D(x,y,z);
}

Vector3D Vector3D::plus(Vector3D b) const {
    return Vector3D(m_x+b.x(), m_y+b.y(), m_z+b.z());
}

Vector3D Vector3D::minus(Vector3D b) const {
    return Vector3D(m_x-b.x(), m_y-b.y(), m_z-b.z());
}

Vector3D Vector3D::times(double scalar) const {
    return Vector3D(scalar*m_x, scalar*m_y, scalar*m_z);
}

meters toMeters(string str) {
    return stod(str);
}

} // BattleRoom namespace

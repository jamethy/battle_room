#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "battle_room/common/resource_descriptor.h"

namespace BattleRoom {

typedef double meters;

class Vector3D {

public:

    Vector3D();
    Vector3D(meters x, meters y, meters z);

    meters& x();
    meters& y();
    meters& z();

    meters dot(Vector3D b);
    Vector3D cross(Vector3D b);
    Vector3D minus(Vector3D b);
    Vector3D times(double scalar);

    void applySettings(ResourceDescriptor settings);

private:

    meters m_x;
    meters m_y;
    meters m_z;

}; // Vector3D class

meters toMeters(std::string str);

} // BattleRoom namespace
#endif // VECTOR3D_H

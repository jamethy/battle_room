#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "battle_room/common/resource_descriptor.h"

namespace BattleRoom {

typedef double meters;

class Vector3D {

public:

    meters& x();
    meters& y();
    meters& z();

    void applySettings(ResourceDescriptor settings);

private:

    meters m_x = 0;
    meters m_y = 0;
    meters m_z = 0;

}; // Vector3D class

meters toMeters(std::string str);

} // BattleRoom namespace
#endif // VECTOR3D_H

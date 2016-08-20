#ifndef QUATERNION_H
#define QUATERNION_H

#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/vector3d.h"

namespace BattleRoom {

class Quaternion {

public:

    Quaternion();
    Quaternion(double w, double i, double j, double k);

    Vector3D getRotated(Vector3D vec);
    Quaternion getRotated(Quaternion p);

    double w();
    double i();
    double j();
    double k();

    void applySettings(ResourceDescriptor settings);

private:

    double m_w = 1;
    double m_i = 0;
    double m_j = 0;
    double m_k = 0;

}; // Quaternion class
} // BattleRoom namespace
#endif // QUATERNION_H

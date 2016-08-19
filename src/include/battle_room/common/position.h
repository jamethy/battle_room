#ifndef POSITION_H
#define POSITION_H

#include "battle_room/common/vector3d.h"
#include "battle_room/common/quaternion.h"
#include "battle_room/common/resource_descriptor.h"

namespace BattleRoom {

typedef double radians;

class Position {

public:

    Vector3D& location();
    Quaternion& orientation();

    Vector3D getLocation();
    Quaternion getOrientation();

    void setLocation(Vector3D location);
    void setOrientation(Quaternion orientation);

    void applySettings(ResourceDescriptor settings);

private:

    Vector3D m_location;
    Quaternion m_orientation;

}; // Position class

radians toRadians(std::string str);

} // BattleRoom namespace
#endif // POSITION_H

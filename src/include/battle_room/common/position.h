#ifndef POSITION_H
#define POSITION_H

#include "battle_room/common/vector3d.h"
#include "battle_room/common/quaternion.h"
#include "battle_room/common/resource_descriptor.h"

namespace BattleRoom {

/**
 * \brief Location and Orientation in 3D space
 */
class Position {

public:

    // Reference Accessors
    Vector3D& location();
    Quaternion& orientation();

    // getters and setters
    Vector3D getLocation();
    Quaternion getOrientation();
    void setLocation(Vector3D location);
    void setOrientation(Quaternion orientation);

    /**
     * \brief Sets the member variables by subs in settings
     * \param settings Descriptor containing location and orientation data
     */
    void applySettings(ResourceDescriptor settings);

private:

    Vector3D m_location; ///< Point in space
    Quaternion m_orientation; ///< Quaternion representing orientation

}; // Position class

/**
 * \brief Utility function to parse string for radians
 * \param str String containing radian value
 * \return Radians that are in str
 */
radians toRadians(std::string str);

} // BattleRoom namespace
#endif // POSITION_H

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "battle_room/common/resource_descriptor.h"

namespace BattleRoom {

/**
 * Unit of measurement in the world coordinates
 */
typedef double meters;

/**
 * \brief Basic 3D vector class with x, y, and z in meters
 */
class Vector3D {

public:

    // constructors 
    Vector3D();
    Vector3D(meters x, meters y, meters z);


    // Access by reference (assigning to these changes the value)
    meters& x();
    meters& y();
    meters& z();

    /**
     * \brief Dot product between this and b
     * \param b Vector to dot with
     * \return Magnitude of dot product
     */
    meters dot(Vector3D b) const;

    /**
     * \brief Cross product between this and b
     * \param b Vector to cross with
     * \return Vector result of cross product
     */
    Vector3D cross(Vector3D b) const;

    /**
     * \brief Returns addition of this to b
     * \param b Vector to add with
     * \return New vector containing result of addition
     */
    Vector3D plus(Vector3D b) const;

    /**
     * \brief Returns copy of this vector minus b
     * \param b Vector to subtract from this
     * \return New vector containing result of subtraction
     */
    Vector3D minus(Vector3D b) const;

    /**
     * \brief Returns copy of this vector multiplied by a scalar
     * \param scalar Scalar value to multiply this vector with
     * \return New vector containing result of multiplication
     */
    Vector3D times(double scalar) const;

    /**
     * \brief Uses the resource descriptor to fill the member variables.
     * \param settings Descriptor with subs of X,Y, and Z
     */
    void applySettings(ResourceDescriptor settings);

private:

    meters m_x; ///< Magnitude in the i direction
    meters m_y; ///< Magnitude in the j direction
    meters m_z; ///< Magnitude in the k direction

}; // Vector3D class

/**
 * \brief Utility function to parse the string for meters
 * \param str String to parse from
 * \return Value in meters found in the string
 */
meters toMeters(std::string str);

} // BattleRoom namespace
#endif // VECTOR3D_H

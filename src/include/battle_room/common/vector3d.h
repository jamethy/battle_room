#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "battle_room/common/resource.h"

namespace BattleRoom {

/**
 * \brief Basic 3D vector class with x, y, and z in meters
 */
    class Vector3D : public Resource {

    public:

        // constructors
        Vector3D();

        Vector3D(meters x, meters y, meters z);

        /**
         * \brief Dot product between this and b
         * \param b Vector to dot with
         * \return Magnitude of dot product
         */
        meters dot(Vector3D b) const;

        /**
         * \brief Returns the magnitude of the vector
         * \return Magnitude of vector
         */
        meters magnitude() const;

        /**
         * \brief Cross product between this and b
         * \param b Vector to cross with
         * \return Vector result of cross product
         */
        Vector3D cross(Vector3D b) const;

        /**
         * \brief Rotate this around b by angle
         * \param b Vector to rotate around
         * \return Vector that has been rotated
         */
        Vector3D rotateAbout(Vector3D b, radians angle) const;

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
         * \brief Returns unit vector in direction of vector
         * \return Unit vector
         */
        Vector3D getUnit() const;

        /**
         * \brief Writes the vector to the string
         * \return String of vector
         */
        std::string toString() const;

        // Access by reference (assigning to these changes the value)
        meters &x();

        meters &y();

        meters &z();

        // inherited
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor writeToSetting(std::string key);

    private:

        meters m_x; ///< Magnitude in the i direction
        meters m_y; ///< Magnitude in the j direction
        meters m_z; ///< Magnitude in the k direction

    }; // Vector3D class
} // BattleRoom namespace
#endif // VECTOR3D_H

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "battle_room/common/resource.h"

namespace BattleRoom {

/**
 * \brief Basic 2D vector class with x, y, and z in meters
 */
    class Vector2D : public Resource {

    public:

        // constructors
        Vector2D();

        Vector2D(meters x, meters y);

        /**
         * \brief Dot product between this and b
         * \param b Vector to dot with
         * \return Magnitude of dot product
         */
        meters dot(Vector2D b) const;

        /**
         * \brief Returns the magnitude of the vector
         * \return Magnitude of vector
         */
        meters magnitude() const;

        /**
         * \brief Returns the angle of the vector from the x-axis
         * \return Angle of vector in radians
         */
        radians angle() const;

        /**
         * \brief Returns addition of this to b
         * \param b Vector to add with
         * \return New vector containing result of addition
         */
        Vector2D plus(Vector2D b) const;

        /**
         * \brief Returns copy of this vector minus b
         * \param b Vector to subtract from this
         * \return New vector containing result of subtraction
         */
        Vector2D minus(Vector2D b) const;

        /**
         * \brief Returns copy of this vector multiplied by a scalar
         * \param scalar Scalar value to multiply this vector with
         * \return New vector containing result of multiplication
         */
        Vector2D times(double scalar) const;

        /**
         * \brief Returns unit vector in direction of vector
         * \return Unit vector
         */
        Vector2D getUnit() const;

        /**
         * \brief Returns a copy of this vector that is rotated by the given angle
         * \param angle Radians to rotate the vector by
         * \return Rotated version of this
         */
        Vector2D getRotated(radians angle) const;

        /**
         * \brief Writes the vector to the string
         * \return String of vector
         */
        std::string toString() const;

        // Access by reference (assigning to these changes the value)
        meters &x();

        meters &y();

        // inherited
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor writeToSetting(std::string key);

    private:

        meters m_x; ///< Magnitude in the i direction
        meters m_y; ///< Magnitude in the j direction

    }; // Vector2D class
} // BattleRoom namespace
#endif // VECTOR2D_H


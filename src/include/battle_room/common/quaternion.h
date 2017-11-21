#ifndef QUATERNION_H
#define QUATERNION_H

#include "battle_room/common/resource.h"
#include "battle_room/common/vector3d.h"

namespace BattleRoom {

    class Quaternion : public Resource {

    public:

        // constructors
        Quaternion();

        Quaternion(radians angle); // angle about z

        Quaternion(double w, double i, double j, double k);

        /**
         * \brief Rotates this quaternion about the Z axis
         * \param angle Angle in radians to rotate
         */
        void rotateAboutZ(radians angle);

        /**
         * \brief Rotates this quaternion about an axis by the given angle
         * \param unit Axis to rotated about
         * \angle Angle to rotate this about
         * \return New Quaternion that is rotated
         */
        Quaternion getRotatedAbout(Vector3D unit, radians angle);

        /**
         * \brief Rotates a copy of vec by this
         *
         * Assumes this quaternion is a unit quaternion
         * Does (inverse(this)) X (vec ) X (this)
         *
         * \param vec Vector to rotate
         * \return Rotated input vector
         */
        Vector3D getRotated(Vector3D vec) const;

        /**
         * \brief Rotates a copy of vec by the inverse of this
         *
         * \param vec Vector to rotate
         * \return Rotated input vector
         */
        Vector3D getInverseRotated(Vector3D vec) const;

        /**
         * \brief Gets a rotated p by this
         *
         * Does (this) X (p)
         *
         * \param p Quaternion to rotate
         * \return Rotated p
         */
        Quaternion getRotated(Quaternion p) const;

        /**
         * \brief Gets the current angle from the vector
         * this is a gross abuse of quaternions // TODO fix that
         *
         * @param v Vector to compare against
         * @return Angle in Radians from v
         */
        radians getAngleFrom(Vector3D v) const;

        /**
         * \brief Gets the current angle from other quaternion
         *
         * @param q Quaternion to compare against
         * @return Angle in Radians from q
         */
        radians getAngleFrom(Quaternion q) const;

        // Access by reference
        double &w();

        double &i();

        double &j();

        double &k();

        // inherited
        void applySettings(ResourceDescriptor settings) override;
        void serialize(BinaryStream& bs) const;
        static Quaternion deserialize(BinaryStream& bs);

    private:

        double m_w = 1;
        double m_i = 0;
        double m_j = 0;
        double m_k = 0;

    }; // Quaternion class
} // BattleRoom namespace
#endif // QUATERNION_H

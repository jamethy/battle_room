#ifndef QUATERNION_H
#define QUATERNION_H

#include "battle_room/common/resource.h"
#include "battle_room/common/vector3d.h"

namespace BattleRoom {

class Quaternion : public Resource {

public:

    // constructors
    Quaternion();
    Quaternion(double w, double i, double j, double k);

    /**
     * \brief Rotates this quaternion about the Z axis
     * \param angle Angle in radians to rotate
     */
    void rotateAboutZ(radians angle);

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
     * \brief Gets a rotated p by this
     *
     * Does (this) X (p)
     *
     * \param p Quaternion to rotate
     * \return Rotated p
     */
    Quaternion getRotated(Quaternion p) const;

    // Access by reference
    double& w();
    double& i();
    double& j();
    double& k();

    // inherited
    void applySettings(ResourceDescriptor settings) override;

private:

    double m_w = 1;
    double m_i = 0;
    double m_j = 0;
    double m_k = 0;

}; // Quaternion class
} // BattleRoom namespace
#endif // QUATERNION_H

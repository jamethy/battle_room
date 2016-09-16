#ifndef PYRAMID_CAMERA_H
#define PYRAMID_CAMERA_H

#include "battle_room/graphics/moving_camera.h"

namespace BattleRoom {

/**
 * \brief Camera implementation that is limited by an invisible pyramid above the 
 * z = 0 plane. The four corners of the pyramid being the plane extremes projected
 * onto the camera plane. It additionally limits the camera by the extremes of the
 * actual z = 0 plane as well.
 */
class PyramidCamera : public MovingCamera {

public:

    // constructors

    PyramidCamera();
    PyramidCamera(ResourceDescriptor settings);
    virtual ~PyramidCamera() override;
    virtual Camera* clone() override;

    // inherited
    void move(Vector3D deltaVelocity);

}; // PyramidCamera class
} // BattleRoom namespace
#endif // PYRAMID_CAMERA_H

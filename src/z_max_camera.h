#ifndef Z_MAX_CAMERA_H
#define Z_MAX_CAMERA_H

#include "moving_camera.h"

namespace BattleRoom {

/**
 * \brief Camera implementation that always remains at the top seeing
 * everything.
 */
    class ZMaxCamera : public MovingCamera {

    public:

        // constructors

        ZMaxCamera();

        ZMaxCamera(ResourceDescriptor settings);

        virtual ~ZMaxCamera() override;

        virtual Camera *clone() override;

        // inherited
        void move(Vector3D deltaVelocity) override;

    }; // ZMaxCamera class
} // BattleRoom namespace
#endif // Z_MAX_CAMERA_H

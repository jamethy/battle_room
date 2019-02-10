#ifndef BATTLE_ROOM_Z_MAX_CAMERA_H
#define BATTLE_ROOM_Z_MAX_CAMERA_H

#include "views/moving_camera.h"

namespace BattleRoom {

/**
 * \brief Camera implementation that always remains at the top seeing
 * everything.
 */
    class ZMaxCamera : public MovingCamera {

    public:

        // constructors

        ZMaxCamera();

        explicit ZMaxCamera(ResourceDescriptor settings);

        ~ZMaxCamera() override;

        Camera *clone() override;

        // inherited
        void move(Vector3D deltaVelocity) override;

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    }; // ZMaxCamera class
} // BattleRoom namespace
#endif // BATTLE_ROOM_Z_MAX_CAMERA_H

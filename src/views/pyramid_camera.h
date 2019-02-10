#ifndef BATTLE_ROOM_PYRAMID_CAMERA_H
#define BATTLE_ROOM_PYRAMID_CAMERA_H

#include "views/moving_camera.h"

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

        explicit PyramidCamera(ResourceDescriptor settings);

        ~PyramidCamera() override;

        Camera *clone() override;

        // inherited
        void move(Vector3D deltaVelocity) override;

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    private:

        Vector3D m_camVelocity; ///< Current velocity of camera

    }; // PyramidCamera class
} // BattleRoom namespace
#endif // BATTLE_ROOM_PYRAMID_CAMERA_H

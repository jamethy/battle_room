#ifndef MOVING_CAMERA_H
#define MOVING_CAMERA_H

#include "battle_room/graphics/camera.h"

namespace BattleRoom {

/**
 * \brief Abstract class for any camera that intends to move
 * Records bounds measured by inputs (using fromLocation)
 */
    class MovingCamera : public Camera {

    public:

        // constructors

        MovingCamera();

        MovingCamera(ResourceDescriptor settings);

        virtual ~MovingCamera() override;

        /**
         * \brief Implementations of this class will move the camera and
         * limit its movements based on the delta velocity given
         * \param deltaVelocity Change in velocity to apply to the camera
         */
        virtual void move(Vector3D deltaVelocity) = 0;

        /**
         * \brief Clears the bounds currently measured
         * This should be called any time the camera is moved. (Its called in
         * the end of handleInputs #cheating)
         */
        void clearBounds();

        /**
         * \brief Adjust the current bounds from the new point attempting to
         * be displayed on the camera's screen
         * \param point Point in 3D space for that the camera's allowed to see
         */
        void adjustForNewPoint(Vector3D &point);


        // inherited
        void rotateCounterClockwise(radians theta) override;

        RelPixel fromLocation(Vector3D location) override;

        Inputs handleInputs(Inputs inputs, const std::string viewName) override;

        void setLocation(Vector3D location) override;

        void setOrientation(Quaternion orientation) override;

        void applySettings(ResourceDescriptor settings) override;

    protected:

        double m_cameraFriction = 0.05; ///< Friction of camera motion
        double m_zoomInMultiplier = 1.0; ///< Multiplier of zooming input
        double m_zoomOutMultiplier = 1.0; ///< Multiplier of zooming input
        meters m_minimumCameraZ = 10;

        Vector3D m_boundsMin; ///< Minimum x and y of point in view
        Vector3D m_boundsMax; ///< Maximum x and y of point in view
        Vector3D m_cameraMin; ///< Minimum point in view in camera coordinates
        Vector3D m_cameraMax; ///< Maximum point in view in camera coordinates

        bool m_rotating = false;
        radians m_originalClick;
        radians m_originalAngle;

    }; // MovingCamera class
} // BattleRoom namespace
#endif // MOVING_CAMERA_H

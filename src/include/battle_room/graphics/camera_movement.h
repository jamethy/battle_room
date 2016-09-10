#ifndef CAMERA_MOVEMENT_H
#define CAMERA_MOVEMENT_H

#include "battle_room/common/resource.h"
#include "battle_room/common/inputs.h"
#include "battle_room/graphics/camera.h"

namespace BattleRoom {

/**
 * Place to put all the camera movement code
 * TODO make a base class and other implementations and a factory
 */
class CameraMovement : public Resource {

public:

    /**
     * \brief Moves the camera based on the detlaV
     * Additionally clears any bounds adjusted
     * \param camera Camera object to move in space
     * \param deltaV 3D velocity vector to add to current velocity of camera
     */
    void moveCamera(Camera& camrea, Vector3D deltaV);

    /**
     * \brief Uses the scroll amount and mouse intersection to create a deltaV for cam
     * \param camera Reference to camera object used for direction
     * \param scrollAmount Scroll wheel movement amount
     * \param mouseIntersection Mouse intersection with z = 0
     * \return A change in velocity to add to camera velocity
     */
    Vector3D deltaVFromScroll(const Camera& camera, int scrollAmount, 
            const Vector3D& mouseIntersection);

    /**
     * \brief Adjusts bounds for new 3D point in the world
     * \param camera Reference to camera used to look at point
     * \param point New point to be adjusted for
     */
    void adjustForNewPoint(const Camera& camera, Vector3D& point);

    // inherited 

    void applySettings(ResourceDescriptor settings) override;

private:

    double m_cameraFriction = 0.05; ///< Friction of camera motion
    double m_zoomInMultiplier = 1.0; ///< Multiplier of zooming input
    double m_zoomOutMultiplier = 1.0; ///< Multiplier of zooming input
    meters m_minimumCameraZ = 10;

    Vector3D m_boundsMin; ///< Minimum x and y of point in view
    Vector3D m_boundsMax; ///< Maximum x and y of point in view
    Vector3D m_cameraMin; ///< Minimum point in view in camera coordinates
    Vector3D m_cameraMax; ///< Maximum point in view in camera coordinates

}; // CameraMovement class
} // BattleRoom namespace
#endif // CAMERA_MOVEMENT_H

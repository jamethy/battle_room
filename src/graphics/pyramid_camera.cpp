#include "battle_room/graphics/pyramid_camera.h"

#include <cmath>

namespace BattleRoom {


// constructors
PyramidCamera::PyramidCamera() 
{ }

PyramidCamera::PyramidCamera(ResourceDescriptor settings)
    : MovingCamera(settings)
{ }

PyramidCamera::~PyramidCamera()
{ }

Camera* PyramidCamera::clone() {
    return new PyramidCamera(*this);
}

void PyramidCamera::move(Vector3D deltaVelocity) {

    static Vector3D camVelocity(0,0,40);

    camVelocity = camVelocity.plus(deltaVelocity);

    if (camVelocity.magnitude() > 0) {

        Vector3D newCamLocation = m_location.plus(camVelocity);

        // check known bounds
        if (newCamLocation.z() < m_minimumCameraZ) { newCamLocation.z() = m_minimumCameraZ; }
        
        if (newCamLocation.x() < m_boundsMin.x()) { newCamLocation.x() = m_boundsMin.x(); }
        else if (newCamLocation.x() > m_boundsMax.x()) { newCamLocation.x() = m_boundsMax.x(); }

        if (newCamLocation.y() < m_boundsMin.y()) { newCamLocation.y() = m_boundsMin.y(); }
        else if (newCamLocation.y() > m_boundsMax.y()) { newCamLocation.y() = m_boundsMax.y(); }


        // Check pyramid bounds

        // calculate the x,y portion of pyramid center/top
        Vector3D pyramidTop = m_boundsMax.plus(m_boundsMin).times(0.5);

        // calculate max z
        pyramidTop.z() = std::max(
                (m_cameraMax.x() - m_cameraMin.x())/(2*std::tan(m_horizontalFov/2.0)),
                (m_cameraMax.y() - m_cameraMin.y())/(2*std::tan(m_verticalFov/2.0))
        ) + m_minimumCameraZ;

        if (newCamLocation.z() > pyramidTop.z()) {
            newCamLocation = pyramidTop;
        }
        else {
            // up dir
            meters upBase = (m_cameraMax.y() - m_cameraMin.y()) / 2.0;
            meters upMax = pyramidTop.y() 
                + upBase*(pyramidTop.z() - newCamLocation.z()) 
                / (pyramidTop.z() - m_minimumCameraZ);

            if ( newCamLocation.y() - pyramidTop.y() > upMax) {
                newCamLocation.y() = upMax + pyramidTop.y();
            }
            else if ( newCamLocation.y() - pyramidTop.y() < -upMax ) {
                newCamLocation.y() = - upMax + pyramidTop.y();
            }

            // right dir
            meters rightBase = (m_cameraMax.x() - m_cameraMin.x()) / 2.0;
            meters rightMax = pyramidTop.x() 
                + rightBase*(pyramidTop.z() - newCamLocation.z()) 
                / (pyramidTop.z() - m_minimumCameraZ);

            if ( newCamLocation.x() - pyramidTop.x() > rightMax) {
                newCamLocation.x() = rightMax + pyramidTop.x();
            }
            else if ( newCamLocation.x() - pyramidTop.x() < -rightMax ) {
                newCamLocation.x() = - rightMax + pyramidTop.x();
            }
        }

        m_location = newCamLocation;

        // adjust velocity
        camVelocity = camVelocity.times(1 - m_cameraFriction);

        if (camVelocity.magnitude() < 0.1) {
            camVelocity = Vector3D(0,0,0);
        }
    }
}

} // BattleRoom namespace

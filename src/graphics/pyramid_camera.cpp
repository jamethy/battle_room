#include "battle_room/graphics/pyramid_camera.h"

#include <cmath>

namespace BattleRoom {

// constructors
PyramidCamera::PyramidCamera() 
{ }

PyramidCamera::PyramidCamera(ResourceDescriptor settings)
    : MovingCamera(settings)
{ 
    m_camVelocity = Vector3D(0,0,0.1);
}

PyramidCamera::~PyramidCamera()
{ }

Camera* PyramidCamera::clone() {
    return new PyramidCamera(*this);
}

void PyramidCamera::move(Vector3D deltaVelocity) {

    m_camVelocity = m_camVelocity.plus(deltaVelocity);

    if (m_camVelocity.magnitude() > 0) {

        Vector3D newCamLocation = m_location.plus(m_camVelocity);

        // check known bounds
        if (newCamLocation.z() < m_minimumCameraZ) { newCamLocation.z() = m_minimumCameraZ; }
        
        if (newCamLocation.x() < m_boundsMin.x()) { newCamLocation.x() = m_boundsMin.x(); }
        else if (newCamLocation.x() > m_boundsMax.x()) { newCamLocation.x() = m_boundsMax.x(); }

        if (newCamLocation.y() < m_boundsMin.y()) { newCamLocation.y() = m_boundsMin.y(); }
        else if (newCamLocation.y() > m_boundsMax.y()) { newCamLocation.y() = m_boundsMax.y(); }


        // Check pyramid bounds

        // calculate the x,y portion of pyramid center/top
        Vector3D pyramidTop = m_right.times( (m_cameraMax.x() + m_cameraMin.x())/2.0 )
            .plus( m_up.times( (m_cameraMax.y() + m_cameraMin.y())/2.0 ));

        // calculate max z
        pyramidTop.z() = std::max(
                (m_cameraMax.x() - m_cameraMin.x())/(2*std::tan(m_horizontalFov/2.0)),
                (m_cameraMax.y() - m_cameraMin.y())/(2*std::tan(m_verticalFov/2.0))
        ) + m_minimumCameraZ;

        if (newCamLocation.z() > pyramidTop.z()) {
            newCamLocation = pyramidTop;
        }
        else {

            // get vector from pyramid to camera
            Vector3D topToCam = newCamLocation.minus(pyramidTop);

            // calculate bound in camera's coordinates for camera's height
            meters upBound = -topToCam.z()*std::tan(m_verticalFov/2.0);
            meters rightBound = -topToCam.z()*std::tan(m_horizontalFov/2.0);

            // calculate where the camera is in camera coordinates relative to pyramid top
            meters upCamOffset = m_up.dot( topToCam );
            meters rightCamOffset = m_right.dot( topToCam );

            if ( upCamOffset > upBound ) {
                newCamLocation = newCamLocation.minus(m_up.times( upCamOffset - upBound ));
            }
            else if ( upCamOffset < -upBound ) {
                newCamLocation = newCamLocation.minus(m_up.times( upCamOffset + upBound ));
            }


            if ( rightCamOffset > rightBound ) {
                newCamLocation = newCamLocation.minus(m_right.times(rightCamOffset - rightBound));
            }
            else if ( rightCamOffset < -rightBound ) {
                newCamLocation = newCamLocation.minus(m_right.times(rightCamOffset + rightBound));
            }

        }

        m_location = newCamLocation;

        // adjust velocity
        m_camVelocity = m_camVelocity.times(1 - m_cameraFriction);

        if (m_camVelocity.magnitude() < 0.1) {
            m_camVelocity = Vector3D(0,0,0);
        }
    }
}

} // BattleRoom namespace

#include "battle_room/graphics/z_max_camera.h"

#include <cmath>

namespace BattleRoom {


// constructors
ZMaxCamera::ZMaxCamera() 
{ }

ZMaxCamera::ZMaxCamera(ResourceDescriptor settings)
    : MovingCamera(settings)
{ }

ZMaxCamera::~ZMaxCamera()
{ }

Camera* ZMaxCamera::clone() {
    return new ZMaxCamera(*this);
}

void ZMaxCamera::move(Vector3D deltaVelocity) {

    (void)deltaVelocity; // unused

    // calculate the x,y portion of pyramid center/top
    Vector3D pyramidTop = m_boundsMax.plus(m_boundsMin).times(0.5);

    // calculate max z
    pyramidTop.z() = std::max(
            (m_cameraMax.x() - m_cameraMin.x())/(2*std::tan(m_horizontalFov/2.0)),
            (m_cameraMax.y() - m_cameraMin.y())/(2*std::tan(m_verticalFov/2.0))
            ) + m_minimumCameraZ;

    m_location = pyramidTop;
}

} // BattleRoom namespace

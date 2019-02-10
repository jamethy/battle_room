#include "views/z_max_camera.h"

#include <cmath>

namespace BattleRoom {

    void ZMaxCamera::applySettings(ResourceDescriptor settings) {
        MovingCamera::applySettings(settings);
    }

    ResourceDescriptor ZMaxCamera::getSettings() const {
        auto rd = MovingCamera::getSettings();
        rd.setValue("ZMax");
        return rd;
    }

// constructors
    ZMaxCamera::ZMaxCamera() = default;

    ZMaxCamera::ZMaxCamera(ResourceDescriptor settings)
            : MovingCamera(std::move(settings)) {}

    ZMaxCamera::~ZMaxCamera() = default;

    Camera *ZMaxCamera::clone() {
        return new ZMaxCamera(*this);
    }

    void ZMaxCamera::move(Vector3D deltaVelocity) {

        (void) deltaVelocity; // unused

        // calculate the x,y portion of pyramid center/top
        Vector3D pyramidTop = m_right.times((m_cameraMax.x() + m_cameraMin.x()) / 2.0)
                .plus(m_up.times((m_cameraMax.y() + m_cameraMin.y()) / 2.0));

        // calculate max z
        pyramidTop.z() = std::max(
                (m_cameraMax.x() - m_cameraMin.x()) / (2 * std::tan(m_horizontalFov / 2.0)),
                (m_cameraMax.y() - m_cameraMin.y()) / (2 * std::tan(m_verticalFov / 2.0))
        ) + m_minimumCameraZ;

        m_location = pyramidTop;
    }

} // BattleRoom namespace

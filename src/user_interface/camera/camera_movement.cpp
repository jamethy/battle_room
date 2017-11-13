#include "battle_room/user_interface/camera/camera_movement.h"

#include <cmath>
#include <limits>

namespace BattleRoom {

    const meters MAX_METERS = std::numeric_limits<double>::max();

// apply settings

    void CameraMovement::applySettings(ResourceDescriptor settings) {

        ResourceDescriptor sub = settings.getSubResource("CameraFriction");
        if (isNotEmpty(sub.getValue())) {
            m_cameraFriction = std::stod(sub.getValue());
        }

        sub = settings.getSubResource("ZoomInMultiplier");
        if (isNotEmpty(sub.getValue())) {
            m_zoomInMultiplier = std::stod(sub.getValue());
        }

        sub = settings.getSubResource("ZoomOutMultiplier");
        if (isNotEmpty(sub.getValue())) {
            m_zoomOutMultiplier = std::stod(sub.getValue());
        }

        sub = settings.getSubResource("MinimumCameraZ");
        if (isNotEmpty(sub.getValue())) {
            m_minimumCameraZ = std::stod(sub.getValue());
        }

    }

// other functions

/**
 * \brief Gets the max x, max y, and max z of either points
 */
    Vector3D getMaxEnds(Vector3D &a, Vector3D &b) {

        Vector3D c = a;
        if (b.x() > c.x()) { c.x() = b.x(); }
        if (b.y() > c.y()) { c.y() = b.y(); }
        if (b.z() > c.z()) { c.z() = b.z(); }
        return c;
    }

/**
 * \brief Gets the min x, min y, and min z of either points
 */
    Vector3D getMinEnds(Vector3D &a, Vector3D &b) {

        Vector3D c = a;
        if (b.x() < c.x()) { c.x() = b.x(); }
        if (b.y() < c.y()) { c.y() = b.y(); }
        if (b.z() < c.z()) { c.z() = b.z(); }
        return c;
    }

    void CameraMovement::adjustForNewPoint(const Camera &camera, Vector3D &point) {

        m_boundsMin = getMinEnds(m_boundsMin, point);
        m_boundsMax = getMaxEnds(m_boundsMax, point);

        Vector3D cameraCoord(
                point.dot(camera.getRightDir()),
                point.dot(camera.getUpDir()),
                0
        );

        m_cameraMin = getMinEnds(m_cameraMin, cameraCoord);
        m_cameraMax = getMaxEnds(m_cameraMax, cameraCoord);
    }

    void CameraMovement::moveCamera(Camera &camera, Vector3D deltaV) {

        static Vector3D camVelocity(0, 0, 40);

        camVelocity = camVelocity.plus(deltaV);

        if (camVelocity.magnitude() > 0) {

            Vector3D newCamLocation = camera.getLocation().plus(camVelocity);

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
                    (m_cameraMax.x() - m_cameraMin.x()) / (2 * std::tan(camera.getHorizontalFov() / 2.0)),
                    (m_cameraMax.y() - m_cameraMin.y()) / (2 * std::tan(camera.getVerticalFov() / 2.0))
            ) + m_minimumCameraZ;

            if (newCamLocation.z() > pyramidTop.z()) {
                newCamLocation = pyramidTop;
            } else {
                // up dir
                meters upBase = (m_cameraMax.y() - m_cameraMin.y()) / 2.0;
                meters upMax = pyramidTop.y()
                               + upBase * (pyramidTop.z() - newCamLocation.z())
                                 / (pyramidTop.z() - m_minimumCameraZ);

                if (newCamLocation.y() - pyramidTop.y() > upMax) {
                    newCamLocation.y() = upMax + pyramidTop.y();
                } else if (newCamLocation.y() - pyramidTop.y() < -upMax) {
                    newCamLocation.y() = -upMax + pyramidTop.y();
                }

                // right dir
                meters rightBase = (m_cameraMax.x() - m_cameraMin.x()) / 2.0;
                meters rightMax = pyramidTop.x()
                                  + rightBase * (pyramidTop.z() - newCamLocation.z())
                                    / (pyramidTop.z() - m_minimumCameraZ);

                if (newCamLocation.x() - pyramidTop.x() > rightMax) {
                    newCamLocation.x() = rightMax + pyramidTop.x();
                } else if (newCamLocation.x() - pyramidTop.x() < -rightMax) {
                    newCamLocation.x() = -rightMax + pyramidTop.x();
                }
            }

            camera.setLocation(newCamLocation);

            // adjust velocity
            camVelocity = camVelocity.times(1 - m_cameraFriction);

            if (camVelocity.magnitude() < 0.1) {
                camVelocity = Vector3D(0, 0, 0);
            }
        }

        m_boundsMin = Vector3D(MAX_METERS, MAX_METERS, MAX_METERS);
        m_boundsMax = Vector3D(-MAX_METERS, -MAX_METERS, -MAX_METERS);
        m_cameraMin = Vector3D(MAX_METERS, MAX_METERS, MAX_METERS);
        m_cameraMax = Vector3D(-MAX_METERS, -MAX_METERS, -MAX_METERS);
    }

    Vector3D
    CameraMovement::deltaVFromScroll(const Camera &camera, int scrollAmount, const Vector3D &mouseIntersection) {

        if (scrollAmount < 0) {
            // MOVE CAMERA UP
            return Vector3D(0, 0, -m_zoomInMultiplier * scrollAmount);
        } else {
            // MOVE CAMERA TOWRAD POS
            return mouseIntersection.minus(camera.getLocation()).getUnit()
                    .times(m_zoomOutMultiplier * scrollAmount);
        }
    }


} // BattleRoom namespace

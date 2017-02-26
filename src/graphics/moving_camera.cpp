#include "battle_room/graphics/moving_camera.h"

#include <cmath>

namespace BattleRoom {

// apply settings

    void MovingCamera::applySettings(ResourceDescriptor settings) {

        Camera::applySettings(settings);

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

// constructors

    MovingCamera::MovingCamera() {

    }

    MovingCamera::MovingCamera(ResourceDescriptor settings) {
        applySettings(settings);
    }

    MovingCamera::~MovingCamera() {
    }

    void MovingCamera::clearBounds() {
        m_boundsMin = Vector3D(MAX_METERS, MAX_METERS, MAX_METERS);
        m_boundsMax = Vector3D(-MAX_METERS, -MAX_METERS, -MAX_METERS);
        m_cameraMin = Vector3D(MAX_METERS, MAX_METERS, MAX_METERS);
        m_cameraMax = Vector3D(-MAX_METERS, -MAX_METERS, -MAX_METERS);
    }

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

    void MovingCamera::adjustForNewPoint(Vector3D &point) {

        m_boundsMin = getMinEnds(m_boundsMin, point);
        m_boundsMax = getMaxEnds(m_boundsMax, point);

        Vector3D cameraCoord(
                point.dot(m_right),
                point.dot(m_up),
                0
        );

        m_cameraMin = getMinEnds(m_cameraMin, cameraCoord);
        m_cameraMax = getMaxEnds(m_cameraMax, cameraCoord);
    }

    Inputs MovingCamera::handleInputs(Inputs inputs, const std::string viewName) {

        Inputs remainingInputs;

        // adjust camera position
        Vector3D camVelocityDelta(0, 0, 0);

        for (Input input : inputs) {

            if (input.containsView(viewName)) {

                if (input.getMotion() == InputKey::Scroll) {

                    if (input.getScrollAmount() < 0) {
                        // MOVE CAMERA UP
                        camVelocityDelta = camVelocityDelta.plus(
                                Vector3D(0, 0, -m_zoomInMultiplier * input.getScrollAmount())
                        );
                    } else {
                        // MOVE CAMERA TOWRAD POS
                        camVelocityDelta = camVelocityDelta.plus(
                                input.getViewIntersection(viewName)
                                        .minus(m_location)
                                        .getUnit()
                                        .times(m_zoomOutMultiplier * input.getScrollAmount())
                        );
                    }
                    continue;
                }
            }

            remainingInputs.addInput(input);
        }

        // Move camera based on input
        move(camVelocityDelta);
        clearBounds();

        // return remaining inputs
        return remainingInputs;
    }

    void MovingCamera::rotateCounterClockwise(radians theta) {
        Camera::rotateCounterClockwise(theta);
        clearBounds();
    }

    RelPixel MovingCamera::fromLocation(Vector3D location) {
        adjustForNewPoint(location);
        return Camera::fromLocation(location);
    }

    void MovingCamera::setLocation(Vector3D location) {
        clearBounds();
        Camera::setLocation(location);
    }

    void MovingCamera::setOrientation(Quaternion orientation) {
        clearBounds();
        Camera::setOrientation(orientation);
    }

} // BattleRoom namespace


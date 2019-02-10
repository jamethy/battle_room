#include "views/moving_camera.h"

#include <cmath>

using InputKey::Key;
using InputKey::Motion;
using InputKey::Modifier;

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

    ResourceDescriptor MovingCamera::getSettings() const {
        ResourceDescriptor rd = Camera::getSettings();
        rd.setValue("MovingCamera");
        std::vector<ResourceDescriptor> subs = rd.getSubResources();

        subs.emplace_back("CameraFriction", std::to_string(m_cameraFriction));
        subs.emplace_back("ZoomInMultiplier", std::to_string(m_zoomInMultiplier));
        subs.emplace_back("ZoomOutMultiplier", std::to_string(m_zoomOutMultiplier));
        subs.emplace_back("MinimumCameraZ", std::to_string(m_minimumCameraZ));

        rd.setSubResources(subs);
        return rd;
    }


// constructors

    MovingCamera::MovingCamera() = default;

    MovingCamera::MovingCamera(ResourceDescriptor settings) {
        applySettings(std::move(settings));
    }

    MovingCamera::~MovingCamera() = default;

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

    Inputs MovingCamera::handleInputs(Inputs inputs, const UniqueId viewId) {

        Inputs remainingInputs;

        // adjust camera position
        Vector3D camVelocityDelta(0, 0, 0);
        radians camRotDelta = 0;

        for (Input input : inputs) {

            if (input.containsView(viewId)) {

                if (Motion::Scroll == input.getMotion()) {

                    if (input.getScrollAmount() < 0) {
                        // MOVE CAMERA UP
                        camVelocityDelta = camVelocityDelta.plus(
                                Vector3D(0, 0, -m_zoomInMultiplier * input.getScrollAmount())
                        );
                    } else {
                        // MOVE CAMERA TOWRAD POS
                        camVelocityDelta = camVelocityDelta.plus(
                                input.getViewIntersection(viewId)
                                        .minus(m_location)
                                        .getUnit()
                                        .times(m_zoomOutMultiplier * input.getScrollAmount())
                        );
                    }
                    continue;
                } else if (input.isModKeyDown(Modifier::Ctrl, Key::LeftClick)) {
                    m_rotating = true;
                    RelPixel point = fromLocation(input.getViewIntersection(viewId));
                    m_originalClick = std::atan2(0.5 - point.getRow(), point.getCol() - 0.5);
                    m_originalAngle = std::atan2(m_right.y(), m_right.x());
                    if (m_originalClick < 0) m_originalClick += 2 * PI;
                    if (m_originalAngle < 0) m_originalAngle += 2 * PI;

                } else if (m_rotating && Key::LeftClick == input.getKey() && Motion::Released == input.getMotion()) {
                    m_rotating = false;
                } else if (m_rotating && Key::MouseOnly == input.getKey()) {
                    RelPixel point = fromLocation(input.getViewIntersection(viewId));
                    radians click = std::atan2(0.5 - point.getRow(), point.getCol() - 0.5);
                    radians currentDelta = std::atan2(m_right.y(), m_right.x());
                    if (click < 0) click += 2 * PI;
                    if (currentDelta < 0) currentDelta += 2 * PI;

                    camRotDelta = (-currentDelta + m_originalAngle - (click - m_originalClick));
                }
            }

            remainingInputs.addInput(input);
        }

        // Move camera based on input
        move(camVelocityDelta);
        rotateCounterClockwise(camRotDelta);
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


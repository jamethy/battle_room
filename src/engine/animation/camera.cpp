#include "battle_room/engine/animation/camera.h"

using std::string;
using std::vector;

namespace BattleRoom {

Position& Camera::position() {
    return m_position;
}

Position Camera::getPosition() {
    return m_position;
}

void Camera::setPosition(Position pos) {
    m_position = pos;
}

void Camera::applySettings(ResourceDescriptor settings) {

    ResourceDescriptor sub = settings.getSubResource("Width");
    if (!sub.getKey().empty()) {
        m_width = toPx(sub.getValue());
    } 

    sub = settings.getSubResource("Height");
    if (!sub.getKey().empty()) {
        m_height = toPx(sub.getValue());
    } 

    sub = settings.getSubResource("HorizontalFieldOfView");
    if (!sub.getKey().empty()) {
        m_horizontalFov = toRadians(sub.getValue());
    } 

    sub = settings.getSubResource("VerticalFieldOfView");
    if (!sub.getKey().empty()) {
        m_verticalFov = toRadians(sub.getValue());
    } 

    sub = settings.getSubResource("Position");
    if (!sub.getKey().empty()) {
        m_position.applySettings(sub);
    } 
}


Pixel Camera::fromZeroPlane(Vector3D location) {
    return Pixel();
}

Vector3D Camera::zeroPlaneIntersection(Pixel pixel) {
    return Vector3D();
}

px Camera::getHeight() {
    return m_height;
}
px Camera::getWidth() {
    return m_width;
}
radians Camera::getHorizontalFov() {
    return m_horizontalFov;
}
radians Camera::getVerticalFov() {
    return m_verticalFov;
}

} // BattleRoom namespace

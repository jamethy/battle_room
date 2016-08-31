#include "battle_room/engine/animation/camera.h"

#include <cmath>

using std::string;
using std::vector;

namespace BattleRoom {
// apply settings

void Camera::applySettings(ResourceDescriptor settings) {

    if (isNotEmpty(settings.getValue())) {
        setName(settings.getValue());
    }

    ResourceDescriptor sub = settings.getSubResource("HorizontalFieldOfView");
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

// constructors

Camera::Camera() 
    : m_name("DEFAULT_CAMERA_NAME"),
    m_forward(Vector3D(0,0,-1)),
    m_up(Vector3D(0,1,0)),
    m_right(Vector3D(1,0,0))
{
    m_position.setLocation(Vector3D(0,0,10));
}

Camera::Camera(ResourceDescriptor settings) : Camera()
{
    applySettings(settings);
}


//setters and getters

string Camera::getName() {
    return m_name;
}

Position Camera::getPosition() {
    return m_position;
}

radians Camera::getHorizontalFov() {
    return m_horizontalFov;
}
radians Camera::getVerticalFov() {
    return m_verticalFov;
}

void Camera::setPosition(Position pos) {
    m_position = pos;
    Quaternion orientation = m_position.getOrientation();
    m_forward = orientation.getRotated(Vector3D(0,0,-1));
    m_up = orientation.getRotated(Vector3D(0,1,0));
    m_right = orientation.getRotated(Vector3D(1,0,0));
}

void Camera::setHorizontalFov(radians angle) {
    m_horizontalFov = angle;
}

void Camera::setVerticalFov(radians angle) {
    m_verticalFov = angle;
}

void Camera::setName(string name) {
    m_name = name;
}

// other functions

void Camera::rotateClockwise(radians theta) {

    Position pos = getPosition();
    Quaternion old = pos.getOrientation();

    double w = cos(theta/2.0);
    double i = m_forward.x()*sin(theta/2.0);
    double j = m_forward.y()*sin(theta/2.0);
    double k = m_forward.z()*sin(theta/2.0);

    Quaternion rot = Quaternion(w,i,j,k);

    pos.setOrientation(rot.getRotated(old));
    setPosition(pos);
}

RelPixel Camera::fromLocation(Vector3D location) {

    Vector3D delta = location.minus(m_position.getLocation());
    meters dist = delta.dot(m_forward);
    meters width = 2*dist*tan(m_horizontalFov / 2.0);
    meters height = 2*dist*tan(m_verticalFov / 2.0);
    Vector3D q = delta.minus( m_forward.times( dist ) );

    meters qx = q.dot(m_right);
    meters qy = q.dot(m_up);
    
    relpx col = (0.5 + qx/width);
    relpx row = (0.5 - qy/height);

    return RelPixel(row,col);
}

Vector3D Camera::zeroPlaneIntersection(RelPixel pixel) {

    radians horiz = m_horizontalFov*(0.5 - pixel.getCol());
    radians verti = m_verticalFov*(0.5 - pixel.getRow());

    Vector3D ray1 = Quaternion(1,0,0,0)
        .getRotatedAbout(m_up, horiz)
        .getRotated(m_right);

    Vector3D ray2 = Quaternion(1,0,0,0)
        .getRotatedAbout(m_right, verti)
        .getRotated(m_up);
    
    Vector3D ray = ray2.cross(ray1);

    Vector3D cam = m_position.getLocation();
    return cam.plus(ray.times( -cam.z() / ray.z() ));
}

// these two functions are not allowed
/*void Camera::rotateUpDown(radians theta) {

    Position pos = getPosition();
    Quaternion old = pos.getOrientation();
    double w = cos(theta/2.0);
    double i = m_right.x()*sin(theta/2.0);
    double j = m_right.y()*sin(theta/2.0);
    double k = m_right.z()*sin(theta/2.0);

    Quaternion rot = Quaternion(w,i,j,k);
    pos.setOrientation(rot.getRotated(old));
    setPosition(pos);
}

void Camera::rotateLeftRight(radians theta) {

    Position pos = getPosition();
    Quaternion old = pos.getOrientation();
    double w = cos(theta/2.0);
    double i = m_up.x()*sin(theta/2.0);
    double j = m_up.y()*sin(theta/2.0);
    double k = m_up.z()*sin(theta/2.0);

    Quaternion rot = Quaternion(w,i,j,k);
    pos.setOrientation(rot.getRotated(old));
    setPosition(pos);
}
*/

} // BattleRoom namespace

#include "views/camera.h"

#include <cmath>

using std::string;
using std::vector;

namespace BattleRoom {
// apply settings

    void Camera::applySettings(ResourceDescriptor settings) {

        m_location.applySettings(settings.getSubResource("Location"));

        Quaternion orientation;
        orientation.applySettings(settings.getSubResource("Orientation"));

        ResourceDescriptor sub = settings.getSubResource("Rotation");
        if (isNotEmpty(sub.getValue())) {
            orientation = Quaternion();
            orientation.rotateAboutZ(toRadians(sub.getValue()));
        }

        sub = settings.getSubResource("DegRotation");
        if (isNotEmpty(sub.getValue())) {
            radians angle = toRadians(toDegrees(sub.getValue()));
            orientation = Quaternion();
            orientation.rotateAboutZ(angle);
        }
        setOrientation(orientation);
    }

    ResourceDescriptor Camera::getSettings() const {
        ResourceDescriptor rd("Camera", "Abstract");
        std::vector<ResourceDescriptor> subs = {};

        ResourceDescriptor sub = m_location.getSettings();
        sub.setKey("Location");
        subs.push_back(sub);

        sub = m_orientation.getSettings();
        sub.setKey("Orientation");
        subs.push_back(sub);

        rd.setSubResources(subs);
        return rd;
    }

// constructors

    Camera::Camera()
            : m_location(Vector3D(0, 0, 99e99)),
              m_forward(Vector3D(0, 0, -1)),
              m_up(Vector3D(0, 1, 0)),
              m_right(Vector3D(1, 0, 0)) {}

    Camera::Camera(ResourceDescriptor settings) : Camera() {
        applySettings(std::move(settings));
    }

    Camera::~Camera() = default;

    Camera *Camera::clone() {
        return new Camera(*this);
    }

//setters and getters

    Vector3D Camera::getLocation() const {
        return m_location;
    }

    Quaternion Camera::getOrientation() const {
        return m_orientation;
    }

    radians Camera::getHorizontalFov() const {
        return m_horizontalFov;
    }

    radians Camera::getVerticalFov() const {
        return m_verticalFov;
    }

    void Camera::setLocation(Vector3D location) {
        m_location = location;
    }

    void Camera::setOrientation(Quaternion orientation) {
        m_orientation = orientation;
        m_forward = orientation.getRotated(Vector3D(0, 0, -1));
        m_up = orientation.getRotated(Vector3D(0, 1, 0));
        m_right = orientation.getRotated(Vector3D(1, 0, 0));
    }

    void Camera::setHorizontalFov(radians angle) {
        m_horizontalFov = angle;
    }

    void Camera::setVerticalFov(radians angle) {
        m_verticalFov = angle;
    }

// other functions

    void Camera::rotateCounterClockwise(radians theta) {
        m_orientation.rotateAboutZ(theta);
        setOrientation(m_orientation);
    }

    RelPixel Camera::fromLocation(Vector3D location) {

        Vector3D delta = location.minus(m_location);
        meters dist = delta.dot(m_forward);
        meters width = 2 * dist * tan(m_horizontalFov / 2.0);
        meters height = 2 * dist * tan(m_verticalFov / 2.0);

        Vector3D q = delta.minus(m_forward.times(dist));

        meters qx = q.dot(m_right);
        meters qy = q.dot(m_up);

        relpx col = (0.5 + qx / width);
        relpx row = (0.5 - qy / height);

        return RelPixel(row, col);
    }

    Vector3D Camera::getPixelRay(RelPixel pixel) const {

        radians horiz = std::atan(2*(0.5 - pixel.getCol())*std::tan(m_horizontalFov/2.0));
        radians verti = std::atan(2*(0.5 - pixel.getRow())*std::tan(m_verticalFov/2.0));

        Vector3D ray1 = Quaternion(1, 0, 0, 0)
                .getRotatedAbout(m_up, horiz)
                .getRotated(m_right);

        Vector3D ray2 = Quaternion(1, 0, 0, 0)
                .getRotatedAbout(m_right, verti)
                .getRotated(m_up);

        return ray2.cross(ray1);
    }

    Vector3D Camera::zeroPlaneIntersection(RelPixel pixel) const {

        Vector3D ray = getPixelRay(pixel);
        Vector3D cam = getLocation();
        Vector3D res = cam.plus(ray.times(-cam.z() / ray.z()));
        return res;
    }

    relpx Camera::zeroPlaneLength(meters dist) const {
        // todo do this right
        return dist / (2 * m_location.getZ() * tan(m_horizontalFov / 2.0));
    }

    Inputs Camera::handleInputs(Inputs inputs, const UniqueId viewId) {
        (void) viewId; // unused
        return inputs;
    }

// these two functions are not allowed
/*void Camera::rotateUpDown(radians theta) {

    Quaternion old = getOrientation();
    double w = cos(theta/2.0);
    double i = m_right.x()*sin(theta/2.0);
    double j = m_right.y()*sin(theta/2.0);
    double k = m_right.z()*sin(theta/2.0);

    Quaternion rot = Quaternion(w,i,j,k);
    setOrientation(rot.getRotated(old));
}

void Camera::rotateLeftRight(radians theta) {

    Quaternion old = getOrientation();
    double w = cos(theta/2.0);
    double i = m_up.x()*sin(theta/2.0);
    double j = m_up.y()*sin(theta/2.0);
    double k = m_up.z()*sin(theta/2.0);

    Quaternion rot = Quaternion(w,i,j,k);
    setOrientation(rot.getRotated(old));
}
*/

} // BattleRoom namespace

#include "vector3d.h"
#include "string_utils.h"

#include <cmath>

using std::string;

namespace BattleRoom {

// apply settings

    void Vector3D::applySettings(ResourceDescriptor settings) {

        std::vector<string> values = split(settings.getValue(), ',');
        if (values.size() == 3 || values.size() == 2) {
            m_x = toMeters(values[0]);
            m_y = toMeters(values[1]);
        }
        if (values.size() == 3) {
            m_z = toMeters(values[2]);
        }

        ResourceDescriptor sub = settings.getSubResource("X");
        if (isNotEmpty(sub.getValue())) {
            m_x = toMeters(sub.getValue());
        }

        sub = settings.getSubResource("Y");
        if (isNotEmpty(sub.getValue())) {
            m_y = toMeters(sub.getValue());
        }

        sub = settings.getSubResource("Z");
        if (isNotEmpty(sub.getValue())) {
            m_z = toMeters(sub.getValue());
        }
    }

    ResourceDescriptor Vector3D::writeToSetting(string key) {
        return ResourceDescriptor(key, toString());
    }

// constructors

    Vector3D::Vector3D()
            : m_x(0.0), m_y(0.0), m_z(0.0) {}

    Vector3D::Vector3D(meters x, meters y, meters z)
            : m_x(x), m_y(y), m_z(z) {}

// Access by reference

    meters &Vector3D::x() {
        return m_x;
    }

    meters &Vector3D::y() {
        return m_y;
    }

    meters &Vector3D::z() {
        return m_z;
    }

// math functions

    meters Vector3D::dot(Vector3D b) const {
        return m_x * b.x() + m_y * b.y() + m_z * b.z();
    }

    meters Vector3D::magnitude() const {
        return std::sqrt(this->dot(*this));
    }

    Vector3D Vector3D::cross(Vector3D b) const {
        meters x = m_y * b.z() - m_z * b.y();
        meters y = m_z * b.x() - m_x * b.z();
        meters z = m_x * b.y() - m_y * b.x();
        return Vector3D(x, y, z);
    }

    Vector3D Vector3D::rotateAbout(Vector3D b, radians angle) const {
        Vector3D par = b.times(this->dot(b)/b.magnitude());
        Vector3D perp = this->minus(par);
        meters perpm = perp.magnitude();

        if (perpm <= EPS_METERS) {
            return *this;
        }

        Vector3D w = b.cross(perp);

        double x1 = std::cos(angle)/perpm;
        double x2 = std::sin(angle)/w.magnitude();

        Vector3D rot = perp.times(x1).plus(w.times(x2)).times(perpm);
        return par.plus(rot);
    }

    Vector3D Vector3D::plus(Vector3D b) const {
        return Vector3D(m_x + b.x(), m_y + b.y(), m_z + b.z());
    }

    Vector3D Vector3D::minus(Vector3D b) const {
        return Vector3D(m_x - b.x(), m_y - b.y(), m_z - b.z());
    }

    Vector3D Vector3D::times(double scalar) const {
        return Vector3D(scalar * m_x, scalar * m_y, scalar * m_z);
    }

    Vector3D Vector3D::getUnit() const {
        meters mag = magnitude();
        if (mag < EPS_METERS) {
            return Vector3D(1, 0, 0);
        } else {
            return this->times(1.0 / mag);
        }
    }

    void Vector3D::serialize(BinaryStream& bs) const {
        bs.writeMeters(m_x);
        bs.writeMeters(m_y);
        bs.writeMeters(m_z);
    }

    Vector3D Vector3D::deserialize(BinaryStream& bs) {
        meters x = bs.readMeters();
        meters y = bs.readMeters();
        meters z = bs.readMeters();
        return Vector3D(x, y, z);
    }


// others

    std::string Vector3D::toString() const {
        return std::to_string(m_x) + ", " +
               std::to_string(m_y) + ", " +
               std::to_string(m_z);
    }

} // BattleRoom namespace

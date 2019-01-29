#include <utility>

#include "vector2d.h"
#include "string_utils.h"

#include <cmath>

using std::string;

namespace BattleRoom {

// apply settings

    void Vector2D::applySettings(ResourceDescriptor settings) {

        std::vector<string> values = split(settings.getValue(), ',');
        if (values.size() == 2) {
            m_x = toMeters(values[0]);
            m_y = toMeters(values[1]);
        }

        ResourceDescriptor sub = settings.getSubResource("X");
        if (isNotEmpty(sub.getValue())) {
            m_x = toMeters(sub.getValue());
        }

        sub = settings.getSubResource("Y");
        if (isNotEmpty(sub.getValue())) {
            m_y = toMeters(sub.getValue());
        }
    }

    ResourceDescriptor Vector2D::getSettings() const {
        return ResourceDescriptor("Vector2D", std::to_string(m_x) + "," + std::to_string(m_y));
    }

// constructors

    Vector2D::Vector2D()
            : m_x(0.0), m_y(0.0) {}

    Vector2D::Vector2D(meters x, meters y)
            : m_x(x), m_y(y) {}

// Access by reference

    meters &Vector2D::x() {
        return m_x;
    }

    meters &Vector2D::y() {
        return m_y;
    }

// math functions

    meters Vector2D::dot(Vector2D b) const {
        return m_x * b.x() + m_y * b.y();
    }

    meters Vector2D::magnitude() const {
        return std::sqrt(this->dot(*this));
    }

    radians Vector2D::angle() const {
        return std::atan2(m_y, m_x);
    }

    Vector2D Vector2D::plus(Vector2D b) const {
        return Vector2D(m_x + b.x(), m_y + b.y());
    }

    Vector2D Vector2D::minus(Vector2D b) const {
        return Vector2D(m_x - b.x(), m_y - b.y());
    }

    Vector2D Vector2D::times(double scalar) const {
        return Vector2D(scalar * m_x, scalar * m_y);
    }

    Vector2D Vector2D::getUnit() const {
        meters mag = magnitude();
        if (mag < EPS_METERS) {
            return Vector2D(1, 0);
        } else {
            return this->times(1.0 / mag);
        }
    }

    Vector2D Vector2D::getRotated(radians angle) const {
        meters x = m_x * std::cos(angle) - m_y * std::sin(angle);
        meters y = m_x * std::sin(angle) + m_y * std::cos(angle);
        return Vector2D(x, y);
    }

    void Vector2D::serialize(BinaryStream &bs) const {
        bs.writeMeters(m_x);
        bs.writeMeters(m_y);
    }

    Vector2D Vector2D::deserialize(BinaryStream &bs) {
        meters x = bs.readMeters();
        meters y = bs.readMeters();
        return Vector2D(x, y);
    }


// others

    std::string Vector2D::toString() const {
        return std::to_string(m_x) + ", " +
               std::to_string(m_y);
    }

    meters Vector2D::getX() const {
        return m_x;
    }

    meters Vector2D::getY() const {
        return m_y;
    }

} // BattleRoom namespace

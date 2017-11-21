#include "battle_room/common/quaternion.h"
#include "battle_room/common/string_utils.h"

#include <cmath>

namespace BattleRoom {

// apply settings

    void Quaternion::applySettings(ResourceDescriptor settings) {

        std::vector<std::string> values = split(settings.getValue(), ',');
        if (values.size() == 4) {
            m_w = toMeters(values[0]);
            m_i = toMeters(values[1]);
            m_j = toMeters(values[2]);
            m_k = toMeters(values[3]);
        }

        ResourceDescriptor sub = settings.getSubResource("W");
        if (isNotEmpty(sub.getValue())) {
            m_w = stod(sub.getValue());
        }

        sub = settings.getSubResource("I");
        if (isNotEmpty(sub.getValue())) {
            m_i = stod(sub.getValue());
        }

        sub = settings.getSubResource("J");
        if (isNotEmpty(sub.getValue())) {
            m_j = stod(sub.getValue());
        }

        sub = settings.getSubResource("K");
        if (isNotEmpty(sub.getValue())) {
            m_k = stod(sub.getValue());
        }
    }

// constructors

    Quaternion::Quaternion()
        : m_w(1.0), m_i(0.0), m_j(0.0), m_k(0.0) {}

    Quaternion::Quaternion(radians angle)
        : m_w(1.0), m_i(0.0), m_j(0.0), m_k(0.0) {
            this->rotateAboutZ(angle);
        }

    Quaternion::Quaternion(double w, double i, double j, double k)
            : m_w(w), m_i(i), m_j(j), m_k(k) {}

    void Quaternion::rotateAboutZ(radians angle) {
        *this = this->getRotatedAbout(Vector3D(0, 0, 1), angle);
    }

    Quaternion Quaternion::getRotatedAbout(Vector3D unit, radians angle) {

        Quaternion rotation(
                std::cos(angle / 2.0),
                std::sin(angle / 2.0) * unit.x(),
                std::sin(angle / 2.0) * unit.y(),
                std::sin(angle / 2.0) * unit.z()
        );

        return rotation.getRotated(*this);
    }

    Vector3D Quaternion::getRotated(Vector3D v) const {

        // qp
        double w = -m_i * v.x() - m_j * v.y() - m_k * v.z();
        double i = m_w * v.x() + m_j * v.z() - m_k * v.y();
        double j = m_w * v.y() - m_i * v.z() + m_k * v.x();
        double k = m_w * v.z() + m_i * v.y() - m_j * v.x();

        // (qp)q'
        //double fw =  w*m_w + i*m_i + j*m_j + k*m_k; // shoud always be zero
        double fi = -w * m_i + i * m_w - j * m_k + k * m_j;
        double fj = -w * m_j + i * m_k + j * m_w - k * m_i;
        double fk = -w * m_k - i * m_j + j * m_i + k * m_w;

        return Vector3D(fi, fj, fk);
    }

    Vector3D Quaternion::getInverseRotated(Vector3D v) const {
        return Quaternion(m_w, -m_i, -m_j, -m_k).getRotated(v);
    }

    Quaternion Quaternion::getRotated(Quaternion p) const {

        // qp
        double w = m_w * p.w() - m_i * p.i() - m_j * p.j() - m_k * p.k();
        double i = m_w * p.i() + m_i * p.w() + m_j * p.k() - m_k * p.j();
        double j = m_w * p.j() - m_i * p.k() + m_j * p.w() + m_k * p.i();
        double k = m_w * p.k() + m_i * p.j() - m_j * p.i() + m_k * p.w();

        return Quaternion(w, i, j, k);
    }

    radians Quaternion::getAngleFrom(Vector3D v) const {
        Vector3D b = getRotated(Vector3D(1, 0, 0));
        return std::atan2(v.y(), v.x()) - std::atan2(b.y(), b.x());
    }

    radians Quaternion::getAngleFrom(Quaternion q) const {
        Vector3D x = getInverseRotated(q.getRotated(Vector3D(1, 0, 0)));
        return std::atan2(x.y(), x.x());
    }

    // Accessors by reference

    double &Quaternion::w() {
        return m_w;
    }

    double &Quaternion::i() {
        return m_i;
    }

    double &Quaternion::j() {
        return m_j;
    }

    double &Quaternion::k() {
        return m_k;
    }

    void Quaternion::serialize(BinaryStream& bs) const {
        bs.writeDouble(m_w);
        bs.writeDouble(m_i);
        bs.writeDouble(m_j);
        bs.writeDouble(m_k);
    }

    Quaternion Quaternion::deserialize(BinaryStream& bs) {
        return Quaternion(
                bs.readDouble(),
                bs.readDouble(),
                bs.readDouble(),
                bs.readDouble());
    }

} // BattleRoom namespace

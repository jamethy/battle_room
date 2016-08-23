#include "battle_room/common/quaternion.h"

#include <iostream>

namespace BattleRoom {

// constructors

Quaternion::Quaternion() 
    : m_w(1.0), m_i(0.0), m_j(0.0), m_k(0.0)
{ }

Quaternion::Quaternion(double w, double i, double j, double k) 
    : m_w(w), m_i(i), m_j(j), m_k(k)
{ }

Vector3D Quaternion::getRotated(Vector3D v) const {

    // qp
    double w =           - m_i*v.x() - m_j*v.y() - m_k*v.z();
    double i = m_w*v.x()             + m_j*v.z() - m_k*v.y();
    double j = m_w*v.y() - m_i*v.z()             + m_k*v.x();
    double k = m_w*v.z() + m_i*v.y() - m_j*v.x();

    // (qp)q'
    //double fw =  w*m_w + i*m_i + j*m_j + k*m_k; // shoud always be zero
    double fi = -w*m_i + i*m_w - j*m_k + k*m_j;
    double fj = -w*m_j + i*m_k + j*m_w - k*m_i;
    double fk = -w*m_k - i*m_j + j*m_i + k*m_w;

    return Vector3D(fi,fj,fk);
}

Quaternion Quaternion::getRotated(Quaternion p) const {
    
    // qp
    double w = m_w*p.w() - m_i*p.i() - m_j*p.j() - m_k*p.k();
    double i = m_w*p.i() + m_i*p.w() + m_j*p.k() - m_k*p.j();
    double j = m_w*p.j() - m_i*p.k() + m_j*p.w() + m_k*p.i();
    double k = m_w*p.k() + m_i*p.j() - m_j*p.i() + m_k*p.w();

    return Quaternion(w,i,j,k);
}

// Accessors by reference

double& Quaternion::w() {
    return m_w;
}

double& Quaternion::i() {
    return m_i;
}

double& Quaternion::j() {
    return m_j;
}

double& Quaternion::k() {
    return m_k;
}

void Quaternion::applySettings(ResourceDescriptor settings) {

    ResourceDescriptor sub = settings.getSubResource("W");
    if (!sub.getKey().empty()) {
        m_w = stod(sub.getValue());
    } 

    sub = settings.getSubResource("I");
    if (!sub.getKey().empty()) {
        m_i = stod(sub.getValue());
    } 

    sub = settings.getSubResource("J");
    if (!sub.getKey().empty()) {
        m_j = stod(sub.getValue());
    } 

    sub = settings.getSubResource("K");
    if (!sub.getKey().empty()) {
        m_k = stod(sub.getValue());
    } 
}

} // BattleRoom namespace

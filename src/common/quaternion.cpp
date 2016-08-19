#include "battle_room/common/quaternion.h"

namespace BattleRoom {

Quaternion::Quaternion() 
    : m_w(1.0), m_i(0.0), m_j(0.0), m_k(0.0)
{ }

Quaternion::Quaternion(double w, double i, double j, double k) 
    : m_w(w), m_i(i), m_j(j), m_k(k)
{ }

double Quaternion::w() {
    return m_w;
}

double Quaternion::i() {
    return m_i;
}

double Quaternion::j() {
    return m_j;
}

double Quaternion::k() {
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

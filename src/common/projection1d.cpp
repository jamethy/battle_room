#include "battle_room/common/projection1d.h"

namespace BattleRoom {

Projection1D::Projection1D() 
    : m_min(MAX_METERS),
    m_max(-MAX_METERS)
{ }

Projection1D::Projection1D(meters min, meters max) 
    : m_min(min),
    m_max(max)
{ }

void Projection1D::adjustForPoint(meters point) {
    if (point < getMin()) {
        setMin(point);
    }
    if (point > getMax()) {
        setMax(point);
    }
}

bool Projection1D::doesNotOverlap(Projection1D other) {

    return getMin() >= other.getMax() || other.getMin() >= getMax();
}

// getters and setters

meters Projection1D::getMin() {
    return m_min;
}

meters Projection1D::getMax() {
    return m_max;
}

void Projection1D::setMin(meters min) {
    m_min = min;
}

void Projection1D::setMax(meters max) {
    m_max = max;
}

} // namespace BattleRoom

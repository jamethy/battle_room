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

bool Projection1D::doesNotOverlap(const Projection1D& other) const {

    return getMin() >= other.getMax() || other.getMin() >= getMax();
}

meters Projection1D::getOverlap(const Projection1D& other) const {

    if (getMax() > other.getMax()) {
        return other.getMax() - getMin();
    }
    else {
        return getMax() - other.getMin();
    }
}

// getters and setters

meters Projection1D::getMid() const {
    return (getMax() + getMin()) / 2.0;
}

meters Projection1D::getMin() const {
    return m_min;
}

meters Projection1D::getMax() const {
    return m_max;
}

void Projection1D::setMin(meters min) {
    m_min = min;
}

void Projection1D::setMax(meters max) {
    m_max = max;
}

} // namespace BattleRoom

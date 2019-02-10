#include "common/sat_intersection.h"

namespace BattleRoom {

    SatIntersection::SatIntersection()
            : m_intersects(false), m_minTranslationMagnitude(MAX_METERS) {
    }

    void SatIntersection::setIntersects(bool intersects) {
        m_intersects = intersects;
    }

    void SatIntersection::setMinTranslationUnitVector(Vector2D vec) {
        m_minTranslationUnit = vec;
    }

    void SatIntersection::setMinTranslationMagnitude(meters mag) {
        m_minTranslationMagnitude = mag;
    }

    bool SatIntersection::doesIntersect() {
        return m_intersects;
    }

    Vector2D SatIntersection::getMinTranslationUnitVector() {
        return m_minTranslationUnit;
    }

    meters SatIntersection::getMinTranslationMagnitude() {
        return m_minTranslationMagnitude;
    }
} // BattleRoom namespace

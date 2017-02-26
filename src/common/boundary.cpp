#include "battle_room/common/boundary.h"

namespace BattleRoom {

    void adjustMinOverlap(SatIntersection &intersection, const Projection1D &proj1, const Projection1D &proj2,
                          const Vector2D &normal) {
        meters overlap = (proj1.getMax() > proj2.getMax())
                         ? proj2.getMax() - proj1.getMin()
                         : proj1.getMax() - proj2.getMin();

        if (overlap < intersection.getMinTranslationMagnitude()) {
            double sign = (proj1.getMid() > proj2.getMid()) ? -1 : 1;
            intersection.setMinTranslationMagnitude(overlap);
            intersection.setMinTranslationUnitVector(normal.times(sign));
        }
    }

    SatIntersection Boundary::intersects(Boundary *other, Vector2D delta, radians angle) const {

        SatIntersection intersection;
        intersection.setIntersects(false);

        if (other == nullptr) { return intersection; }

        for (Vector2D normal : getSideNormals()) {

            // get this projection
            Projection1D thisProj = projectOnto(normal);

            // get other projection
            meters deltaProj = normal.dot(delta);
            Vector2D rotatedNormal = normal.getRotated(-angle);

            Projection1D otherProj = other->projectOnto(rotatedNormal);
            otherProj.setMin(otherProj.getMin() + deltaProj);
            otherProj.setMax(otherProj.getMax() + deltaProj);

            if (thisProj.doesNotOverlap(otherProj)) {
                return intersection;
            }
            adjustMinOverlap(intersection, thisProj, otherProj, normal);
        }

        for (Vector2D normal : other->getSideNormals()) {

            // get this projection
            Vector2D rotatedNormal = normal.getRotated(angle);
            Projection1D thisProj = projectOnto(rotatedNormal);

            // get other projection
            meters deltaProj = rotatedNormal.dot(delta);
            Projection1D otherProj = other->projectOnto(normal);
            otherProj.setMin(otherProj.getMin() + deltaProj);
            otherProj.setMax(otherProj.getMax() + deltaProj);

            if (thisProj.doesNotOverlap(otherProj)) {
                return intersection;
            }
            adjustMinOverlap(intersection, thisProj, otherProj, rotatedNormal);
        }

        // mainly just for circle to circle, check axis of delta
        Vector2D unitDelta = delta.getUnit();
        Projection1D thisProj = projectOnto(unitDelta);

        meters deltaProj = unitDelta.dot(delta);
        Vector2D rotatedNormal = unitDelta.getRotated(-angle);


        Projection1D otherProj = other->projectOnto(rotatedNormal);
        otherProj.setMin(otherProj.getMin() + deltaProj);
        otherProj.setMax(otherProj.getMax() + deltaProj);
        if (thisProj.doesNotOverlap(otherProj)) {
            return intersection;
        }
        adjustMinOverlap(intersection, thisProj, otherProj, unitDelta);

        intersection.setIntersects(true);
        return intersection;
    }


} // BattleRoom namespace

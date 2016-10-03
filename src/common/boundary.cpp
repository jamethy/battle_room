#include "battle_room/common/boundary.h"

namespace BattleRoom {


bool Boundary::intersects(Boundary* other, Vector2D delta, radians angle) {

    if (other == nullptr) { return false; }

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
            return false;
        }
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
            return false;
        }
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
        return false;
    }

    return true;
}


} // BattleRoom namespace

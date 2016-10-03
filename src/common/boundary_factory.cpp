#include "battle_room/common/boundary_factory.h"
#include "battle_room/common/circle_boundary.h"
#include "battle_room/common/box_boundary.h"

namespace BattleRoom {

//////////////////////////////////////////////////////////////
// Empty Boundary class
class EmptyBoundary : public Boundary {

    bool intersects(Boundary* other, Vector2D delta, radians angle) override {
        (void)other; (void) delta; (void) angle; // unused
        return false;
    }

    bool contains(Vector2D delta) override {
        (void)delta;
        return false;
    }

    Projection1D projectOnto(Vector2D axis) override {
        (void)axis; // unused
        return Projection1D();
    }

    std::vector<Vector2D> getSideNormals() override {
        return std::vector<Vector2D>();
    }

    void applySettings(ResourceDescriptor settings) override {
        (void)settings;
    }
}; // EmptyBoundary class

//////////////////////////////////////////////////////////////
// Boundary Factory class
UniqueBoundary BoundaryFactory::createBoundary(ResourceDescriptor settings) {

    if ( keyMatch("Circle", settings.getValue()) ) {
        return UniqueBoundary(new CircleBoundary(settings));
    }
    else if ( keyMatch("Box", settings.getValue()) ) {
        return UniqueBoundary(new BoxBoundary(settings));
    }
    else {
        return createEmptyBoundary();
    }
}

UniqueBoundary BoundaryFactory::createEmptyBoundary() {
    return UniqueBoundary(new EmptyBoundary());
}
} // BattleRoom namespace

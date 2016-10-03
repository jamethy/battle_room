#ifndef CIRCLE_BOUNDARY_H
#define CIRCLE_BOUNDARY_H

#include "battle_room/common/boundary.h"

namespace BattleRoom {

class CircleBoundary : public Boundary {

public:

    CircleBoundary(ResourceDescriptor settings);

    // inherited
    bool contains(Vector2D delta);
    void applySettings(ResourceDescriptor settings);

protected:

    Projection1D projectOnto(Vector2D axis) override;
    std::vector<Vector2D> getSideNormals() override;

private:

    Vector2D m_center; ///< Center point relative to center of object
    meters m_radius; ///< Radius of circle

}; // CircleBoundary class
} // BattleRoom namespace
#endif // CIRCLE_BOUNDARY_H

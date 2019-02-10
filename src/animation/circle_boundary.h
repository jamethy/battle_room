#ifndef BATTLE_ROOM_CIRCLE_BOUNDARY_H
#define BATTLE_ROOM_CIRCLE_BOUNDARY_H

#include "animation/boundary.h"

namespace BattleRoom {

    class CircleBoundary : public Boundary {

    public:

        explicit CircleBoundary(ResourceDescriptor settings);

        // inherited
        bool contains(Vector2D delta) const override;

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        Boundary *clone() const override;

    protected:

        Projection1D projectOnto(Vector2D axis) const override;

        std::vector<Vector2D> getSideNormals() const override;

    private:

        Vector2D m_center; ///< Center point relative to center of object
        meters m_radius; ///< Radius of circle

    }; // CircleBoundary class
} // BattleRoom namespace
#endif // BATTLE_ROOM_CIRCLE_BOUNDARY_H

#ifndef BATTLE_ROOM_CIRCLE_BOUNDARY_H
#define BATTLE_ROOM_CIRCLE_BOUNDARY_H

#include "animation/boundary.h"

namespace BattleRoom {

    /**
     * Boundary defined by a simple circle
     *
     * Resource:
     *
     * Boundary: Circle
     *   Center: <vector2D>
     *   Radius: <meters>
     */
    class CircleBoundary : public Boundary {

    public:

        /// construct

        explicit CircleBoundary(ResourceDescriptor settings);

        /// inherited from Resource

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        /// inherited from Boundary

        bool contains(Vector2D delta) const override;

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

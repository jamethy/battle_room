#ifndef BATTLE_ROOM_BOX_BOUNDARY_H
#define BATTLE_ROOM_BOX_BOUNDARY_H

#include "animation/boundary.h"

namespace BattleRoom {

    /**
     * Boundary that is a simple four-sided object. Can be a rectangle or
     * a non-parallelagram object
     *
     * Resource:
     *
     * Boundary: Box
     *   Center: <Vector2D>
     *   Width: <meters>
     *   Height: <meters>
     *   Rotation: <radians>
     *   DegRotation: <degrees>
     */
    class BoxBoundary : public Boundary {

    public:

        /// constructors

        explicit BoxBoundary(ResourceDescriptor settings);

        /// inherited from Boundary

        bool contains(Vector2D delta) const override;

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        Boundary *clone() const override;

    protected:

        Projection1D projectOnto(Vector2D axis) const override;

        std::vector<Vector2D> getSideNormals() const override;

    private:

        std::vector<Vector2D> m_corners;
        std::vector<Vector2D> m_sideNormals;

    }; // BoxBoundary class
} // BattleRoom namespace
#endif // BATTLE_ROOM_BOX_BOUNDARY_H

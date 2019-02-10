#ifndef BATTLE_ROOM_BOUNDARY_SET_H
#define BATTLE_ROOM_BOUNDARY_SET_H

#include "animation/boundary.h"

#include <vector>

namespace BattleRoom {

    /**
     * A set of boundaries acting together as one
     */
    class BoundarySet {

    public:

        /// constructors/destructors

        BoundarySet();

        explicit BoundarySet(std::vector<ResourceDescriptor> boundarySettings);

        BoundarySet(const BoundarySet &original);

        BoundarySet &operator=(const BoundarySet &original);

        ~BoundarySet();

        static UniqueBoundary createBoundary(ResourceDescriptor settings);

        /// beginning iterator of boundary set
        std::vector<Boundary *>::const_iterator begin() const;

        /// ending iterator of boundary set
        std::vector<Boundary *>::const_iterator end() const;

        /**
         * Checks if the point is within the boundary
         * \param delta Point is in the object's frame of reference
         * \return True if boundary contains point
         */
        bool contains(Vector2D delta) const;

        /**
         * "Flatten" the boundary onto a 1D axis - this is essentially the "shadow" of the
         * boundary if the light source behind the axis perpendicular to the axis.
         * @param axis Line to project boundary onto
         * @return Projected values
         */
        Projection1D projectOnto(Vector2D axis) const;

    private:

        std::vector<Boundary *> m_boundaries;

    }; // BoundarySet class
} // BattleRoom namespace
#endif // BATTLE_ROOM_BOUNDARY_SET_H

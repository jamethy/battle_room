#ifndef BATTLE_ROOM_BOUNDARY_H
#define BATTLE_ROOM_BOUNDARY_H

#include "common/resource.h"
#include "common/vector2d.h"
#include "common/projection1d.h"
#include "common/sat_intersection.h"

#include <vector>
#include <memory>

namespace BattleRoom {

    /**
     * Abstract class for physical boundaries in the 3D world
     * Uses children to calculate collisions.
     */
    class Boundary : public Resource {

    public:

        /**
         * Checks if the boundary intersects the other
         * \param other Other boundary to compare against
         * \param delta other's parent location relative to this parent object
         * \param angle Angle difference between two objects
         * \return True if intersecting
         */
        virtual SatIntersection intersects(Boundary *other, Vector2D delta, radians angle) const;

        /**
         * Checks if the point is within the boundary
         * \param delta Point is in the object's frame of reference
         * \return True if boundary contains point
         */
        virtual bool contains(Vector2D delta) const = 0;

        /**
         * Deep copy the boundary
         * @return Deep copy of this boundary
         */
        virtual Boundary *clone() const = 0;

        /**
         * "Flatten" the boundary onto a 1D axis - this is essentially the "shadow" of the
         * boundary if the light source behind the axis perpendicular to the axis.
         * @param axis Line to project boundary onto
         * @return Projected values
         */
        virtual Projection1D projectOnto(Vector2D axis) const = 0;

    protected:

        /**
         * @return List of vectors that are perpendicular to the flat sides of the boundary
         */
        virtual std::vector<Vector2D> getSideNormals() const = 0;

    }; // Boundary class

    typedef std::unique_ptr<Boundary> UniqueBoundary;

} // BattleRoom namespace
#endif // BATTLE_ROOM_BOUNDARY_H

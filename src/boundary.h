#ifndef BOUNDARY_H
#define BOUNDARY_H

#include "resource.h"
#include "vector2d.h"
#include "projection1d.h"
#include "sat_intersection.h"

#include <vector>
#include <memory>

namespace BattleRoom {

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

        virtual Boundary *clone() const = 0;

        virtual Projection1D projectOnto(Vector2D axis) const = 0;

    protected:

        virtual std::vector<Vector2D> getSideNormals() const = 0;

    }; // Boundary class

    typedef std::unique_ptr<Boundary> UniqueBoundary;

} // BattleRoom namespace
#endif // BOUNDARY_H
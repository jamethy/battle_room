#ifndef BOX_BOUNDARY_H
#define BOX_BOUNDARY_H

#include "battle_room/common/boundary.h"

namespace BattleRoom {

    class BoxBoundary : public Boundary {

    public:

        BoxBoundary(ResourceDescriptor settings);

        // inherited
        bool contains(Vector2D delta) const;

        void applySettings(ResourceDescriptor settings);

        Boundary *clone() const;

    protected:

        Projection1D projectOnto(Vector2D axis) const override;

        std::vector<Vector2D> getSideNormals() const override;

    private:

        std::vector<Vector2D> m_corners;
        std::vector<Vector2D> m_sideNormals;

    }; // BoxBoundary class
} // BattleRoom namespace
#endif // BOX_BOUNDARY_H

#ifndef BOX_BOUNDARY_H
#define BOX_BOUNDARY_H

#include "boundary.h"

namespace BattleRoom {

    class BoxBoundary : public Boundary {

    public:

        explicit BoxBoundary(ResourceDescriptor settings);

        // inherited
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
#endif // BOX_BOUNDARY_H

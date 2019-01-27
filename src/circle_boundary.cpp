#include <utility>

#include "circle_boundary.h"

namespace BattleRoom {

// apply settings

    void CircleBoundary::applySettings(ResourceDescriptor settings) {

        m_center.applySettings(settings.getSubResource("Center"));

        ResourceDescriptor sub = settings.getSubResource("Radius");
        if (isNotEmpty(sub.getValue())) {
            m_radius = toMeters(sub.getValue());
        }
    }

    ResourceDescriptor CircleBoundary::getSettings() const {
        ResourceDescriptor rd("Boundary", "Box");
        std::vector<ResourceDescriptor> subs = {};

        ResourceDescriptor sub = m_center.getSettings();
        sub.setKey("Center");
        subs.push_back(sub);

        subs.emplace_back("Radius", std::to_string(m_radius));

        rd.setSubResources(subs);
        return rd;
    }

// constructor

    CircleBoundary::CircleBoundary(ResourceDescriptor settings)
            : m_center(Vector2D(0, 0)),
              m_radius(0) {
        applySettings(std::move(settings));
    }

    Boundary *CircleBoundary::clone() const {
        return new CircleBoundary(*this);
    }


// other functions

    bool CircleBoundary::contains(Vector2D delta) const {
        return m_radius >= delta.minus(m_center).magnitude();
    }

    Projection1D CircleBoundary::projectOnto(Vector2D axis) const {
        (void) axis; // unused
        return {-m_radius, m_radius};
    }

    std::vector<Vector2D> CircleBoundary::getSideNormals() const {
        std::vector<Vector2D> returnvec;
        returnvec.clear();
        return returnvec;
    }

} // BattleRoom namespace

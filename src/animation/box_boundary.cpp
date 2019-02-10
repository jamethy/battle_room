#include "animation/box_boundary.h"

namespace BattleRoom {

// apply settings

    void BoxBoundary::applySettings(ResourceDescriptor settings) {

        Vector2D center(0, 0);
        meters width = 1;
        meters height = 1;
        radians angle = 0;


        center.applySettings(settings.getSubResource("Center"));

        ResourceDescriptor sub = settings.getSubResource("Width");
        if (isNotEmpty(sub.getValue())) {
            width = toMeters(sub.getValue());
        }

        sub = settings.getSubResource("Height");
        if (isNotEmpty(sub.getValue())) {
            height = toMeters(sub.getValue());
        }

        sub = settings.getSubResource("Rotation");
        if (isNotEmpty(sub.getValue())) {
            angle = toRadians(sub.getValue());
        }

        sub = settings.getSubResource("DegRotation");
        if (isNotEmpty(sub.getValue())) {
            angle = toRadians(toDegrees(sub.getValue()));
        }

        // recalculate the corner
        std::vector<Vector2D> unrotated_corners = {
                Vector2D(-width / 2.0, height / 2.0),
                Vector2D(width / 2.0, height / 2.0),
                Vector2D(width / 2.0, -height / 2.0),
                Vector2D(-width / 2.0, -height / 2.0)
        };

        m_corners.clear();
        for (const auto &corner : unrotated_corners) {
            m_corners.push_back(center.plus(corner.getRotated(angle)));
        }

        // recalculate side normals
        m_sideNormals.clear();
        m_sideNormals = {
                Vector2D(1, 0).getRotated(angle),
                Vector2D(0, 1).getRotated(angle)
        };

    }

    ResourceDescriptor BoxBoundary::getSettings() const {
        ResourceDescriptor rd("Boundary", "Box");
        std::vector<ResourceDescriptor> subs = {};

        Vector2D center(0, 0);
        for (const auto &corner : m_corners) {
            center.x() += corner.getX();
            center.y() += corner.getY();
        }
        center.x() /= m_corners.size();
        center.y() /= m_corners.size();

        ResourceDescriptor sub = center.getSettings();
        sub.setKey("Center");
        subs.push_back(sub);

        Vector2D sideNormal = m_sideNormals[1];
        const radians angle = sideNormal.angle();

        // logic probably wrong, but not what I need right now
        Vector2D unrotatedCorner = m_corners[0].getRotated(-angle).minus(center);
        meters width = -unrotatedCorner.getX() * 2.0;
        meters height = unrotatedCorner.getY() * 2.0;

        subs.emplace_back("Rotation", std::to_string(angle));
        subs.emplace_back("Width", std::to_string(width));
        subs.emplace_back("Height", std::to_string(height));

        rd.setSubResources(subs);
        return rd;
    }

// constructor
    BoxBoundary::BoxBoundary(ResourceDescriptor settings) {
        applySettings(std::move(settings));
    }

    Boundary *BoxBoundary::clone() const {
        return new BoxBoundary(*this);
    }

// other functions

    bool BoxBoundary::contains(Vector2D delta) const {
        Vector2D top = m_corners[1].minus(m_corners[0]);
        Vector2D left = m_corners[3].minus(m_corners[0]);
        Vector2D point = delta.minus(m_corners[0]);

        bool underTop = 0 < point.dot(top) && point.dot(top) < top.dot(top);
        bool besideLeft = 0 < point.dot(left) && point.dot(left) < left.dot(left);

        return underTop && besideLeft;
    }

    Projection1D BoxBoundary::projectOnto(Vector2D axis) const {

        Projection1D projection;
        for (const auto &corner : m_corners) {
            projection.adjustForPoint(corner.dot(axis));
        }
        return projection;
    }

    std::vector<Vector2D> BoxBoundary::getSideNormals() const {
        return m_sideNormals;
    }

} // BattleRoom namespace

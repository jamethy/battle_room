#include "boundary_set.h"
#include "circle_boundary.h"
#include "box_boundary.h"

namespace BattleRoom {

//////////////////////////////////////////////////////////////
// Empty Boundary class
    class EmptyBoundary : public Boundary {

        Boundary *clone() const override {
            return new EmptyBoundary(*this);
        }

        SatIntersection intersects(Boundary *other, Vector2D delta, radians angle) const override {
            (void) other;
            (void) delta;
            (void) angle; // unused
            SatIntersection intersection;
            return intersection;
        }

        bool contains(Vector2D delta) const override {
            (void) delta;
            return false;
        }

        Projection1D projectOnto(Vector2D axis) const override {
            (void) axis; // unused
            return Projection1D();
        }

        std::vector<Vector2D> getSideNormals() const override {
            return std::vector<Vector2D>();
        }

        void applySettings(ResourceDescriptor settings) override {
            (void) settings;
        }
    }; // EmptyBoundary class


//////////////////////////////////////////////////////////////
// BoundarySet class

    BoundarySet::BoundarySet() {
        m_boundaries.clear();
    }

    Boundary *createBoundaryPtr(ResourceDescriptor settings) {

        if (keyMatch("Circle", settings.getValue())) {
            return new CircleBoundary(settings);
        } else if (keyMatch("Box", settings.getValue())) {
            return new BoxBoundary(settings);
        } else {
            return new EmptyBoundary();
        }
    }

    UniqueBoundary BoundarySet::createBoundary(ResourceDescriptor settings) {
        return UniqueBoundary(createBoundaryPtr(settings));
    }

    BoundarySet::BoundarySet(std::vector<ResourceDescriptor> boundarySettings)
            : BoundarySet() {
        for (ResourceDescriptor setting : boundarySettings) {
            m_boundaries.push_back(createBoundaryPtr(setting));
        }
    }

    BoundarySet::BoundarySet(const BoundarySet &original) {

        m_boundaries.clear();
        for (Boundary *boundary : original.m_boundaries) {
            m_boundaries.push_back(boundary->clone());
        }
    }

    BoundarySet &BoundarySet::operator=(const BoundarySet &original) {

        m_boundaries.clear();
        for (Boundary *boundary : original.m_boundaries) {
            m_boundaries.push_back(boundary->clone());
        }
        return *this;
    }

    BoundarySet::~BoundarySet() {
        for (Boundary *boundary : m_boundaries) {
            delete boundary;
        }
    }

    std::vector<Boundary *>::const_iterator BoundarySet::begin() const {
        return m_boundaries.begin();
    }

    std::vector<Boundary *>::const_iterator BoundarySet::end() const {
        return m_boundaries.end();
    }

    bool BoundarySet::contains(Vector2D delta) const {
        for (auto b : m_boundaries) {
            if (b->contains(delta)) {
                return true;
            }
        }
        return false;
    }

    Projection1D BoundarySet::projectOnto(Vector2D axis) const {
        Projection1D proj;
        for (auto b : m_boundaries) {
            proj.adjustForProjection(b->projectOnto(axis));
        }
        return proj;
    }

} // BattleRoom namespace

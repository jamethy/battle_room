#ifndef BOUNDARY_SET_H
#define BOUNDARY_SET_H

#include "battle_room/common/boundary.h"

#include <vector>

namespace BattleRoom {

class BoundarySet {

public:

    BoundarySet();
    BoundarySet(std::vector<ResourceDescriptor> boundarySettings);
    BoundarySet(const BoundarySet& original);
    BoundarySet& operator=(const BoundarySet& original);
    ~BoundarySet();

    static UniqueBoundary createBoundary(ResourceDescriptor settings);

    std::vector<Boundary*>::iterator begin();
    std::vector<Boundary*>::iterator end();

private:

    std::vector<Boundary*> m_boundaries;

}; // BoundarySet class
} // BattleRoom namespace
#endif // BOUNDARY_SET_H

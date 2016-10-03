#ifndef BOUNDARY_FACTORY_H
#define BOUNDARY_FACTORY_H

#include "battle_room/common/boundary.h"

namespace BattleRoom {

class BoundaryFactory {

public:


    static UniqueBoundary createBoundary(ResourceDescriptor settings);

    static UniqueBoundary createEmptyBoundary();


}; // BoundaryFactory class
} // BattleRoom namespace
#endif // BOUNDARY_FACTORY_H

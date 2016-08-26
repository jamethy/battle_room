#ifndef INPUT_H
#define INPUT_H

#include "battle_room/common/unique_id.h"
#include "battle_room/common/vector3d.h"

#include <vector>

namespace BattleRoom {

class Input {

public:

private:

    std::string m_viewName;
    Vector3D m_zeroPlaneIntersection;
    std::vector<UniqueId> m_idsOnLocation;
    
    // keys currently down?
    // Keys pressed and released?
    // mouse movement?
        // Start locations
        // end locations

}; // Input class
} // BattleRoom namespace
#endif // INPUT_H

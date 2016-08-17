#ifndef POSITION_H
#define POSITION_H

#include "battle_room/common/location.h"
#include "battle_room/common/orientation.h"

namespace BattleRoom {

class Position {

public:

    Location& location();
    Orientation& orientation();

    Location getLocation();
    Orientation getOrientation();

    void setLocation(Location location);
    void setOrientation(Orientation orientation);

private:

    Location m_location;
    Orientation m_orientation;

}; // Position class
} // BattleRoom namespace
#endif // POSITION_H

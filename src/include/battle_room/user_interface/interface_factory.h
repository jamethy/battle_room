#ifndef INTERFACE_FACTORY_H
#define INTERFACE_FACTORY_H

#include "battle_room/common/view_interface.h"

namespace BattleRoom {

/**
 * Static class for creating View Interfaces
 */
    class InterfaceFactory {

    public:

        static UniqueInterface createInterface(ResourceDescriptor settings, int windowWidth, int windowHeight);

    }; // InterfaceFactory class
} // BattleRoom namespace
#endif // INTERFACE_FACTORY_H


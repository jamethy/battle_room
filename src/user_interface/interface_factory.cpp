#include "battle_room/user_interface/interface_factory.h"
#include "battle_room/user_interface/game_interface.h"
#include "battle_room/user_interface/menu_interface.h"

namespace BattleRoom {

    UniqueInterface InterfaceFactory::createInterface(ResourceDescriptor settings, int windowWidth, int windowHeight) {

        if (keyMatch("Menu", settings.getValue())) {
            return UniqueInterface(new MenuInterface(settings, windowWidth, windowHeight));
        } else {
            return UniqueInterface(new GameInterface(settings, windowWidth, windowHeight));
        }

        // TODO create a blank interface
    }

} // BattleRoom namespace


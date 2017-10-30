#include "battle_room/user_interface/menu.h"

namespace BattleRoom {

    Menu::Menu() : 
        m_uniqueId(UniqueId::generateNewLocalId()) {
    }

    UniqueId Menu::getUniqueId() {
        return m_uniqueId;
    }

} // BattleRoom namespace

#include "battle_room/user_interface/menu.h"

namespace BattleRoom {

    Menu::Menu() : 
        m_uniqueId(UniqueId::generateNewLocalId()) {
    }

    bool Menu::objectBoundaryContains(const DrawableMenu& menu, RelPixel point) {

        Vector2D relP = Vector2D(point.getCol(), point.getRow())
            .minus(menu.getLocation());

        return menu.getAnimation()
            .getFrame(menu.getAnimationState())
            .getBoundarySet()
            .contains(relP);
    }

    UniqueId Menu::getUniqueId() {
        return m_uniqueId;
    }

} // BattleRoom namespace

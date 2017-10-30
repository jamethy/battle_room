#include "battle_room/user_interface/menu.h"

namespace BattleRoom {

    Menu::Menu() : 
        m_uniqueId(UniqueId::generateNewLocalId()) {
    }

    bool Menu::objectBoundaryContains(const DrawableMenu& obj, RelPixel point) {

        Vector2D objLoc = obj.getLocation();

        if (point.getRow() < objLoc.y() - obj.getHeight()/2.0 
                || point.getRow() > objLoc.y() + obj.getHeight()/2.0) {
            return false;
        }

        if (point.getCol() < objLoc.y() - obj.getHeight()/2.0 
                || point.getCol() > objLoc.y() + obj.getHeight()/2.0) {
            return false;
        }

        return true;
    }

    UniqueId Menu::getUniqueId() {
        return m_uniqueId;
    }

} // BattleRoom namespace

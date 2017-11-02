#include "battle_room/user_interface/menu.h"

namespace BattleRoom {

    Menu::Menu() : 
        m_uniqueId(UniqueId::generateNewLocalId()) 
    {}

    bool Menu::objectBoundaryContains(const DrawableMenu& obj, RelPixel point) {

        RelPixel topLeft = obj.getTopLeft();
        RelPixel botRight = obj.getBottomRight();

        if (point.getRow() < topLeft.getRow() || point.getRow() > botRight.getRow()) {
            return false;
        }

        if (point.getCol() < topLeft.getCol() || point.getCol() > botRight.getCol()) {
            return false;
        }

        return true;
    }

    UniqueId Menu::getUniqueId() {
        return m_uniqueId;
    }

} // BattleRoom namespace

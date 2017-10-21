#include "battle_room/user_interface/menu.h"

namespace BattleRoom {

    Menu::Menu() : 
        m_uniqueId(UniqueId::generateNewLocalId()) {
        m_texts.clear();
        m_menus.clear();
    }

    bool objectBoundaryContains(const DrawableMenu& menu, RelPixel point) {

        Vector2D relP = Vector2D(point.getCol(), point.getRow())
            .minus(menu.getLocation());

        return menu.getAnimation()
            .getFrame(menu.getAnimationState())
            .getBoundarySet()
            .contains(relP);
    }

    bool Menu::contains(RelPixel point) {
        for (const auto& obj : m_menus) {
            if (objectBoundaryContains(obj, point)) {
                return true;
            }
        }
        return false;
    }

    std::vector<DrawableText> Menu::getDrawableTexts() {
        return m_texts;
    }

    std::vector<DrawableMenu> Menu::getDrawableMenus() {
        return m_menus;
    }

    UniqueId Menu::getUniqueId() {
        return m_uniqueId;
    }

} // BattleRoom namespace

#include "battle_room/user_interface/pull_down_menu.h"
#include "battle_room/common/animation_handler.h"

namespace BattleRoom {

    PullDownMenu::PullDownMenu() {
        m_pullDown.setAnimation(AnimationHandler::getAnimation("menus/pull_down"));
        m_pullDown.setLocation(Vector2D(0.046666, 0.02));
    }

    bool PullDownMenu::handleInput(Input input, RelPixel point) {
        if (objectBoundaryContains(m_pullDown, point)) {

            return true;
        }
        return false;
    }

    void PullDownMenu::updateAnimation(seconds timestep) {
        m_pullDown.updateAnimation(timestep);
    }

    std::vector<DrawableText> PullDownMenu::getDrawableTexts() {
        return std::vector<DrawableText>();
    }

    std::vector<DrawableMenu> PullDownMenu::getDrawableMenus() {
        return { m_pullDown };
    }

} // BattleRoom namespace


#include "battle_room/user_interface/pull_down_menu.h"
#include "battle_room/common/animation_handler.h"

namespace BattleRoom {

    PullDownMenu::PullDownMenu() {
        DrawableMenu pullDown;
        pullDown.setAnimation(AnimationHandler::getAnimation("menus/pull_down"));
        pullDown.setLocation(Vector2D(0.046666, 0.02));
        m_menus.push_back(pullDown);
    }

} // BattleRoom namespace

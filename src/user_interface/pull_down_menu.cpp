#include "battle_room/user_interface/pull_down_menu.h"
#include "battle_room/common/animation_handler.h"
#include "battle_room/common/application_message.h"
#include "battle_room/common/application_message_receiver.h"

#include <iostream>

using InputKey::Key;

namespace BattleRoom {

    void PullDownMenu::applySettings(ResourceDescriptor settings) {
        m_pullDown.applySettings(settings);
    }

    PullDownMenu::PullDownMenu() {
        m_pullDown.setAnimation(AnimationHandler::getAnimation("menus/pull_down"));
        m_pullDown.setTopLeft(RelPixel(-0.5, 0));
        m_pullDown.setBottomRight(RelPixel(0.5, 1));
    }

    bool PullDownMenu::handleInput(Input input, RelPixel point) {
        if (objectBoundaryContains(m_pullDown, point)) {
            if (input.isKeyDown(Key::LeftClick)) {
                std::cout << "here.\n";
            } else if (input.isKeyUp(Key::LeftClick)) {
            }

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

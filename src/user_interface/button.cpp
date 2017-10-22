#include "battle_room/user_interface/button.h"
#include "battle_room/common/animation_handler.h"

using InputKey::Key;

namespace BattleRoom {

    Button::Button() {
        m_button.setAnimation(AnimationHandler::getAnimation("menus/button_up"));
        m_button.setLocation(Vector2D(0.5, 0.5));
    }

    bool Button::handleInput(Input input, RelPixel point) {
        if (objectBoundaryContains(m_button, point)) {

            if (input.isKeyDown(Key::LeftClick)) {
                m_button.setAnimation(AnimationHandler::getAnimation("menus/button_down"));
            } else if (input.isKeyUp(Key::LeftClick)) {
                m_button.setAnimation(AnimationHandler::getAnimation("menus/button_up"));
            }

            return true;
        }
        return false;
    }

    void Button::updateAnimation(seconds timestep) {
        m_button.updateAnimation(timestep);
    }

    std::vector<DrawableText> Button::getDrawableTexts() {
        return std::vector<DrawableText>();
    }

    std::vector<DrawableMenu> Button::getDrawableMenus() {
        return { m_button };
    }

} // BattleRoom namespace


#include "battle_room/user_interface/button.h"
#include "battle_room/common/animation_handler.h"
#include "battle_room/common/application_message_receiver.h"

#include <iostream>
using InputKey::Key;

namespace BattleRoom {

    void Button::applySettings(ResourceDescriptor settings) {
        m_button.applySettings(settings);

        ResourceDescriptor sub = settings.getSubResource("OnClick");
        if (isNotEmpty(sub.getValue())) {
            std::vector<ApplicationMessage> messages;
            messages.clear();

            if (keyMatch("quit", sub.getValue())) {
                messages.push_back(ApplicationMessage::quit());
            } else {
                ResourceDescriptor resource = ResourceDescriptor::readResource(sub.getValue());
                for (const auto& resSub : resource.getSubResources()) {
                    messages.push_back(ApplicationMessage::add(resSub));
                }
                messages.push_back(ApplicationMessage::remove(getUniqueId()));
            }
            setOnClick(messages);
        }
    }

    Button::Button(UniqueId menuId) :
        Menu(menuId),
        m_buttonDown(false)
    {
        m_button.setAnimation(AnimationHandler::getAnimation("menus/button_up"));
    }

    bool Button::handleInput(Input input, RelPixel point) {
        if (objectBoundaryContains(m_button, point)) {

            if (input.isKeyDown(Key::LeftClick)) {
                m_buttonDown = true;
                m_button.setAnimation(AnimationHandler::getAnimation("menus/button_down"));
            } else if (input.isKeyUp(Key::LeftClick)) {
                m_buttonDown = false;
                m_button.setAnimation(AnimationHandler::getAnimation("menus/button_up"));
                ApplicationMessageReceiver::addMessages(getOnClick());
            }

            return true;
        }
        m_buttonDown = false;
        return false;
    }

    void Button::updateAnimation(seconds timestep) {
        if (m_buttonDown) {
            m_button.setAnimation(AnimationHandler::getAnimation("menus/button_down"));
        } else {
            m_button.setAnimation(AnimationHandler::getAnimation("menus/button_up"));
        }
        m_button.updateAnimation(timestep);
    }

    std::vector<DrawableText> Button::getDrawableTexts() {
        return std::vector<DrawableText>();
    }

    std::vector<DrawableMenu> Button::getDrawableMenus() {
        return { m_button };
    }

    // getters and setters
    std::vector<ApplicationMessage> Button::getOnClick() const {
        return m_onClick;
    }

    void Button::setOnClick(std::vector<ApplicationMessage> messages) {
        m_onClick = messages;
    }

} // BattleRoom namespace


#include "pull_down_menu.h"
#include "animation_handler.h"
#include "application_message_receiver.h"

#include <iostream>

using InputKey::Key;

namespace BattleRoom {

    void PullDownMenu::applySettings(ResourceDescriptor settings) {
        m_pullDown.applySettings(settings);

        ResourceDescriptor sub = settings.getSubResource("OnClick");
        if (isNotEmpty(sub.getValue())) {
            ResourceDescriptor resource = ResourceDescriptor::readResource(sub.getValue());
            std::vector<ApplicationMessage> messages;
            messages.clear();
            for (const auto& resSub : resource.getSubResources()) {
                messages.push_back(ApplicationMessage::add(resSub));
            }
            messages.push_back(ApplicationMessage::remove(getUniqueId()));
            setOnClick(messages);
        }
    }

    PullDownMenu::PullDownMenu(UniqueId menuId) :
        Menu(menuId)
    {
        m_pullDown.setAnimation(AnimationHandler::getAnimation("menus/pull_down"));
        m_pullDown.setTopLeft(RelPixel(-0.5, 0));
        m_pullDown.setBottomRight(RelPixel(0.5, 1));
    }

    bool PullDownMenu::handleInput(Input input, RelPixel point) {
        if (objectBoundaryContains(m_pullDown, point)) {
            if (input.isKeyUp(Key::LeftClick)) {
                ApplicationMessageReceiver::addMessages(getOnClick());
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

    // getters and setters
    std::vector<ApplicationMessage> PullDownMenu::getOnClick() const {
        return m_onClick;
    }

    void PullDownMenu::setOnClick(std::vector<ApplicationMessage> messages) {
        m_onClick = messages;
    }
} // BattleRoom namespace

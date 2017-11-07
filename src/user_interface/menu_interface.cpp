#include "battle_room/user_interface/menu_interface.h"
#include "battle_room/user_interface/pull_down_menu.h"
#include "battle_room/user_interface/button.h"

#include "battle_room/common/input_gatherer.h"
#include "battle_room/common/application_message_receiver.h"

#include <iostream>

using std::vector;
using InputKey::Key;
using InputKey::Motion;
using InputKey::Modifier;

namespace BattleRoom {

// apply settings

    void MenuInterface::applySettings(ResourceDescriptor settings) {

        for (ResourceDescriptor &objDesc : settings.getSubResources("Menu")) {

            Menu* m = nullptr;

            if (keyMatch("PullDown", objDesc.getValue())) {
                m = new PullDownMenu(getUniqueId());
            } else if (keyMatch("Button", objDesc.getValue())) {
                m = new Button(getUniqueId());
            }

            if (m) {
                m->applySettings(objDesc);
                m_menus.push_back(UniqueMenu(m));
            }
        }

        ViewInterface::applySettings(settings);
    }

// constructors

    MenuInterface::MenuInterface(ResourceDescriptor settings, UniqueId viewId) :
        ViewInterface(viewId)
    {
        m_menus.clear();
        applySettings(settings);
    }

// other functions

    vector<DrawableObject> MenuInterface::getDrawableObjects() {
        vector<DrawableObject> objects;
        objects.clear();
        return objects;
    }

    vector<DrawableText> MenuInterface::getDrawableTexts() {
        vector<DrawableText> texts;
        texts.clear();
        for (auto& menu : m_menus) {
            vector<DrawableText> menuDrawables = menu->getDrawableTexts();
            texts.insert(texts.end(), menuDrawables.begin(), menuDrawables.end());
        }

        return texts;
    }

    vector<DrawableMenu> MenuInterface::getDrawableMenus() {
        vector<DrawableMenu> drawables;
        drawables.clear();

        for (auto& menu : m_menus) {
            vector<DrawableMenu> menuDrawables = menu->getDrawableMenus();
            drawables.insert(drawables.end(), menuDrawables.begin(), menuDrawables.end());
        }

        return drawables;
    }

    void MenuInterface::updateAnimations(seconds timestep) {
        for (auto& menu : m_menus) {
            menu->updateAnimation(timestep);
        }
    }

    Inputs MenuInterface::handleInputs(Inputs inputs) {

        Inputs remainingInputs;

        for (Input input : inputs) {

            bool inputHandled = false;

            // temp for easy testing and quitting
            if (input.getMotion() == Motion::PressedDown) {
                if (input.getKey() == Key::Q) {
                    ApplicationMessageReceiver::addQuitEvent();
                }
            }

            if (input.containsView(getAssociatedView())) {

                RelPixel point = input.getViewRelIntersection(getAssociatedView());

                for (auto& menu : m_menus) {
                    if (menu->handleInput(input, point)) {
                        inputHandled = true;
                    }
                }
                //if (input.isKeyDown(Key::LeftClick) || input.isKeyDown(Key::DoubleClick)) {
            }

            if (!inputHandled) {
                remainingInputs.addInput(input);
            }
        }

        return remainingInputs;
    }

    vector<ResourceDescriptor> MenuInterface::getNewSettings() {
        return vector<ResourceDescriptor>();
    }

} // BattleRoom namespace


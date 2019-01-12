#include "menu_interface.h"
#include "pull_down_menu.h"
#include "button.h"

#include "input_gatherer.h"
#include "application_message_receiver.h"

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

        View::applySettings(settings);
    }

// constructors

    MenuInterface::MenuInterface(ResourceDescriptor settings, int windowWidth, int windowHeight) :
        View(settings, windowWidth, windowHeight)
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

    void MenuInterface::update(seconds timestep) {
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

            if (input.containsView(getUniqueId())) {

                RelPixel point = input.getViewRelIntersection(getUniqueId());

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

} // BattleRoom namespace

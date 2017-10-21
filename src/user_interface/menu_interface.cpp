#include "battle_room/user_interface/menu_interface.h"

#include "battle_room/common/input_gatherer.h"
#include <iostream>

using std::vector;
using InputKey::Key;
using InputKey::Motion;
using InputKey::Modifier;

namespace BattleRoom {

// apply settings

    void MenuInterface::applySettings(ResourceDescriptor settings) {

        for (ResourceDescriptor &objDesc : settings.getSubResources("Menu")) {
            DrawableMenu menu;
            menu.applySettings(objDesc);
            m_menus.push_back(menu);
        }

        ViewInterface::applySettings(settings);
    }

// constructors

    MenuInterface::MenuInterface(ResourceDescriptor settings) {
        applySettings(settings);
    }

// other functions

    vector<DrawableObject> MenuInterface::getDrawableObjects() {

        vector<DrawableObject> objects;
        objects.clear();

        return objects;
    }

    vector<DrawableText> MenuInterface::getDrawableTexts() {
        return vector<DrawableText>();
    }

    vector<DrawableMenu> MenuInterface::getDrawableMenus() {
        return m_menus;
    }

    bool objectBoundaryContains(DrawableMenu& menu, RelPixel point) {

        Vector2D relP = Vector2D(point.getCol(), point.getRow())
            .minus(menu.getLocation());

        return menu.getAnimation()
            .getFrame(menu.getAnimationState())
            .getBoundarySet()
            .contains(relP);
    }

    Inputs MenuInterface::handleInputs(Inputs inputs) {

        Inputs remainingInputs;

        for (Input input : inputs) {

            // temp for easy testing and quitting
//            if (input.getMotion() == Motion::PressedDown) {
//                if (input.getKey() == Key::Q) {
//                    InputGatherer::addQuitEvent();
//                }
//            }

            if (input.containsView(getAssociatedView())) {

                RelPixel point = input.getViewRelIntersection(getAssociatedView());

                if (input.isKeyDown(Key::LeftClick) || input.isKeyDown(Key::DoubleClick)) {

                    for (auto& menu : m_menus) {
                        if (objectBoundaryContains(menu, point)) {
                            std::cout << "here\n";
                        }
                    }

                } 
            }

            remainingInputs.addInput(input);
        }

        return remainingInputs;
    }

    vector<ResourceDescriptor> MenuInterface::getNewSettings() {
        return vector<ResourceDescriptor>();
    }

} // BattleRoom namespace


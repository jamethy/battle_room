#include "menu_interface.h"

#include "input_gatherer.h"
#include "application_message_receiver.h"
#include "Logger.h"

using std::vector;
using InputKey::Key;
using InputKey::Motion;

namespace BattleRoom {

// apply settings

    void MenuInterface::applySettings(ResourceDescriptor settings) {
        View::applySettings(settings);
    }

// constructors

    MenuInterface::MenuInterface(ResourceDescriptor settings, TextureManager *textureManager, int windowWidth,
                                 int windowHeight) :
            View(settings, windowWidth, windowHeight),
            m_htmlMenu(new HtmlMenu(textureManager, windowWidth, windowHeight)),
            m_hasFocus(true) {
        applySettings(settings);
    }

// other functions

    vector<DrawableObject> MenuInterface::getDrawableObjects() {
        return {};
    }

    vector<DrawableText> MenuInterface::getDrawableTexts() {
        return {};
    }

    vector<DrawableMenu> MenuInterface::getDrawableMenus() {
        return {m_htmlMenu->getDrawableMenu()};
    }

    void MenuInterface::update(seconds timestep) {
        (void) timestep; // unused
    }

    Inputs MenuInterface::handleInputs(Inputs inputs) {

        Inputs remainingInputs;

        for (Input input : inputs) {

            // temp for easy testing and quitting
            if (input.getMotion() == Motion::PressedDown) {
                if (input.getKey() == Key::Q) {
                    ApplicationMessageReceiver::addQuitEvent();
                }
            }

            if (m_hasFocus && input.containsView(getUniqueId())) {

                RelPixel point = input.getViewRelIntersection(getUniqueId());
                int x = point.getColInt(getViewWdith());
                int y = point.getRowInt(getViewHeight());

                m_htmlMenu->handleInput(input, x, y);
            } else {
                remainingInputs.addInput(input);
            }
        }

        return remainingInputs;
    }

    void MenuInterface::adjustForResize(int width, int height, int oldWidth, int oldHeight) {
        View::adjustForResize(width, height, oldWidth, oldHeight);
        m_htmlMenu->resize(width, height);
    }
} // BattleRoom namespace


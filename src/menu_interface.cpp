#include "menu_interface.h"

#include "input_gatherer.h"
#include "application_message_receiver.h"
#include "logger.h"

#include "include/cef_parser.h"

using std::vector;
using InputKey::Key;
using InputKey::Motion;

namespace BattleRoom {

// apply settings

    void MenuInterface::applySettings(ResourceDescriptor settings) {
        View::applySettings(settings);

        ResourceDescriptor sub = settings.getSubResource("Url");
        if (isNotEmpty(sub.getValue())) {
            m_htmlMenu->navigateTo(sub.getValue());
        }
    }

// constructors

    MenuInterface::MenuInterface(ResourceDescriptor settings, TextureManager *textureManager, int windowWidth,
                                 int windowHeight) :
            View(settings, windowWidth, windowHeight),
            m_htmlMenu(new HtmlMenu(textureManager, windowWidth, windowHeight, this)),
            m_hasFocus(false) {
        applySettings(settings);
    }

// other functions

    std::string MenuInterface::onMessage(const std::string &message) {
        static int counter = 0;

        CefString request(message);
        CefRefPtr<CefDictionaryValue> requestValue = CefParseJSON(request, JSON_PARSER_RFC)->GetDictionary();

        CefRefPtr<CefDictionaryValue> result_dict = CefDictionaryValue::Create();
        result_dict->SetInt("count", ++counter);

        CefRefPtr<CefValue> value = CefValue::Create();
        value->SetDictionary(result_dict);
        CefString json = CefWriteJSON(value, JSON_WRITER_DEFAULT);
        return json.ToString();
    }

    vector<DrawableObject> MenuInterface::getDrawableObjects() {
        return {};
    }

    vector<DrawableText> MenuInterface::getDrawableTexts() {
        return {};
    }

    vector<DrawableMenu> MenuInterface::getDrawableMenus() {
        if (m_hasFocus) {
            return {m_htmlMenu->getDrawableMenu()};
        } else {
            return {};
        }
    }

    void MenuInterface::update(seconds timestep) {
        (void) timestep; // unused
    }

    Inputs MenuInterface::handleInputs(Inputs inputs) {

        Inputs remainingInputs;

        for (Input input : inputs) {

            bool inputHandled = false;

            // temp for easy testing and quitting
            if (input.getMotion() == Motion::PressedDown && input.getKey() == Key::Q) {
                ApplicationMessageReceiver::addQuitEvent();
                inputHandled = true;
            }

            if (input.getMotion() == Motion::PressedDown && input.getKey() == Key::Escape) {
                m_hasFocus = !m_hasFocus;
                inputHandled = true;
            } else if (m_hasFocus) {
                if (input.containsView(getUniqueId())) {

                    RelPixel point = input.getViewRelIntersection(getUniqueId());
                    int x = point.getColInt(getViewWdith());
                    int y = point.getRowInt(getViewHeight());

                    m_htmlMenu->handleInput(input, x, y);
                    inputHandled = true;
                }
            }

            if (!inputHandled) {
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


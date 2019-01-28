#include "menu_interface.h"

#include "input_gatherer.h"
#include "application_message_receiver.h"
#include "logger.h"

#include "include/cef_parser.h"

using std::vector;

namespace BattleRoom {

    using InputKey::Key;
    using InputKey::Motion;

// apply settings

    void MenuInterface::applySettings(ResourceDescriptor settings) {
        View::applySettings(settings);

        ResourceDescriptor sub = settings.getSubResource("Url");
        if (isNotEmpty(sub.getValue())) {
            url = sub.getValue();
            m_htmlMenu->navigateTo(url);
        }
    }

    ResourceDescriptor MenuInterface::getSettings() const {
        auto rd = View::getSettings();
        rd.setValue("Menu");
        auto subs = rd.getSubResources();

        subs.emplace_back("Url", url);

        rd.setSubResources(subs);
        return rd;
    }

// constructors

    MenuInterface::MenuInterface(ResourceDescriptor settings, TextureManager *textureManager, int windowWidth,
                                 int windowHeight, Application *application) :
            View(settings, windowWidth, windowHeight),
            m_htmlMenu(new HtmlMenu(textureManager, windowWidth, windowHeight, this)),
            m_hasFocus(false),
            m_application(application) {
        applySettings(settings);
    }

// other functions

    WebMessageResponse MenuInterface::onMessage(const std::string &message) {

        CefRefPtr<CefDictionaryValue> requestValue = CefParseJSON(CefString(message), JSON_PARSER_RFC)->GetDictionary();
        auto method = requestValue->GetString("method").ToString();
        auto route = requestValue->GetString("route").ToString();
        Log::debug("MenuInterface Message: Method: ", method, ", Route: ", route);

        std::string response;

        if (method == "POST" && route == "/quit") {
            ApplicationMessageReceiver::quit();
            return {WebMessageResponse::SUCCESS_CODE, ""};

        } else if (method == "POST" && route == "/test") {
            auto body = requestValue->GetString("body").ToString();
            ResourceDescriptor resourceDescriptor = ResourceDescriptor::fromJson(body);
            for (const auto &sub : resourceDescriptor.getSubResources()) {
                ApplicationMessageReceiver::addMessage(ApplicationMessage::add(sub));
            }
        } else if (method == "GET" && route == "/application") {
            auto applicationState = m_application->getSettings();
            response = ResourceDescriptor::toJson(applicationState);
        }
        return {WebMessageResponse::SUCCESS_CODE, response};
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
                ApplicationMessageReceiver::quit();
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


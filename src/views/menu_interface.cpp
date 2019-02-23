#include "views/menu_interface.h"

#include "application/input_gatherer.h"
#include "application/application_message_receiver.h"
#include "common/logger.h"

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

        sub = settings.getSubResource("IsShowing");
        if (keyMatch("false", sub.getValue())) {
            m_htmlMenu->hide();
        }
    }

    ResourceDescriptor MenuInterface::getSettings() const {
        auto rd = View::getSettings();
        rd.emplaceSubResource("Type", "Menu");
        rd.emplaceSubResource("Url", url);
        return rd;
    }

// constructors

    MenuInterface::MenuInterface(ResourceDescriptor settings, TextureManager *textureManager, int windowWidth,
                                 int windowHeight, Application *application) :
            View(settings, windowWidth, windowHeight),
            m_htmlMenu(new HtmlMenu(textureManager, windowWidth, windowHeight, this)),
            m_application(application) {
        applySettings(settings);
    }

// other functions

    WebMessageResponse MenuInterface::onMessage(const std::string &message) {

        CefRefPtr<CefDictionaryValue> requestValue = CefParseJSON(CefString(message), JSON_PARSER_RFC)->GetDictionary();
        auto method = requestValue->GetString("method").ToString();
        auto route = requestValue->GetString("route").ToString();
        Log::debug("MenuInterface Message: Method: ", method, ", Route: ", route);

        int responseCode = WebMessageResponse::SUCCESS_CODE;
        std::string response;

        if (method == "POST" && route == "/quit") {
            ApplicationMessageReceiver::quit();

        } else if (method == "POST" && route == "/close") {
            m_htmlMenu->hide();

        } else if (method == "POST" && route == "/message") {
            auto body = requestValue->GetString("body").ToString();
            ResourceDescriptor resourceDescriptor = ResourceDescriptor::fromJson(body);
            ApplicationMessageReceiver::addMessage(ApplicationMessage::add(resourceDescriptor));

        } else if (method == "GET" && route == "/application") {
            auto applicationState = m_application->getSettings();
            response = ResourceDescriptor::toJson(applicationState);

        } else {
            responseCode = WebMessageResponse::NOT_FOUND_CODE;
        }

        return {responseCode, response};
    }

    vector<DrawableObject> MenuInterface::getDrawableObjects() {
        return {};
    }

    vector<DrawableMenu> MenuInterface::getDrawableMenus() {
        if (m_htmlMenu->isShowing()) {
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
                if (m_htmlMenu->isShowing()) {
                    m_htmlMenu->hide();
                } else {
                    m_htmlMenu->show();
                }
                inputHandled = true;
            } else if (m_htmlMenu->isShowing()) {
                if (input.containsView(getUniqueId())) {

                    RelPixel point = input.getViewRelIntersection(getUniqueId());
                    int x = point.getColInt(getViewWidth());
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


#include "menu_interface.h"

#include "input_gatherer.h"
#include "application_message_receiver.h"
#include "Logger.h"

using std::vector;
using InputKey::Key;
using InputKey::Motion;
using InputKey::Modifier;

namespace BattleRoom {

// apply settings

    void MenuInterface::applySettings(ResourceDescriptor settings) {

        //m_drawableMenu.applySettings(settings);
        View::applySettings(settings);
    }

// constructors

    MenuInterface::MenuInterface(ResourceDescriptor settings, TextureManager *textureManager, int windowWidth,
                                 int windowHeight) :
            View(settings, windowWidth, windowHeight) {
        Log::debug("Creating menu interface");
        m_webRenderer = new WebRenderer(textureManager, windowWidth, windowHeight);
        m_webBrowserClient = new WebBrowserClient(m_webRenderer);

        // some browser settings
        CefWindowInfo window_info;
        window_info.SetAsWindowless(kNullWindowHandle);

        CefBrowserSettings browserSettings;
        browserSettings.windowless_frame_rate = 60;
        browserSettings.background_color = 0; // allows for transparency

        // Create the browser object to interpret the HTML
        std::string htmlFile = "file://" + std::string(SDL_GetBasePath()) + "sdl_cef_html.html";
        m_webBrowser = CefBrowserHost::CreateBrowserSync(window_info,
                                                         m_webBrowserClient,
                                                         htmlFile,
                                                         browserSettings,
                                                         nullptr);
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
        return {m_drawableMenu};
    }

    void MenuInterface::update(seconds timestep) {
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
                //browser send key events, etc
            }

            if (!inputHandled) {
                remainingInputs.addInput(input);
            }
        }

        return remainingInputs;
    }

    void MenuInterface::onResize() {
        m_webBrowser->GetHost()->WasResized();
    }

} // BattleRoom namespace


#include "menu_interface.h"

#include "input_gatherer.h"
#include "application_message_receiver.h"
#include "Logger.h"

using std::vector;
using InputKey::Key;
using InputKey::Motion;
using InputKey::Modifier;

namespace BattleRoom {

    typedef struct KeyCodes {
        int key_code;
        int char_code;

        KeyCodes(int keyCode, int charCode) :
                key_code(keyCode), char_code(charCode) {
        }

        char16 getChar16() {
            return static_cast<char16>(char_code);
        }
    } KeyCodes;

    KeyCodes getAlphabetCodes() {
        int diff = 0;
        return {
                65 + diff,
                ('A') + diff
        };
    }

// apply settings

    void MenuInterface::applySettings(ResourceDescriptor settings) {

        m_drawableMenu.setBottomRight(RelPixel(1, 1));
        m_drawableMenu.setTextureKey(m_webRenderer->getTextureKey());
        View::applySettings(settings);
    }

// constructors

    MenuInterface::MenuInterface(ResourceDescriptor settings, TextureManager *textureManager, int windowWidth,
                                 int windowHeight) :
            View(settings, windowWidth, windowHeight) {
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
        Log::debug("Creating menu with dimensions [", windowWidth, ", ", windowHeight, "] of ", htmlFile);
        m_webBrowser = CefBrowserHost::CreateBrowserSync(window_info,
                                                         m_webBrowserClient,
                                                         htmlFile,
                                                         browserSettings,
                                                         nullptr);
        applySettings(settings);
        m_webBrowser->GetHost()->WasResized();
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


                CefMouseEvent event;
                event.x = point.getColInt(getViewWdith());
                event.y = point.getRowInt(getViewHeight());

                CefKeyEvent keyEvent;
                KeyCodes keyCodes = getAlphabetCodes();
                keyEvent.type = KEYEVENT_KEYDOWN;
                keyEvent.windows_key_code = keyCodes.key_code;
                keyEvent.native_key_code = keyCodes.key_code;
                keyEvent.character = keyCodes.getChar16();
                keyEvent.unmodified_character = keyCodes.getChar16();

                switch (input.getKey()) {
                    case Key::MouseOnly:
                        m_webBrowser->GetHost()->SendMouseMoveEvent(event, false);
                        break;
                    case Key::LeftClick:
                        m_webBrowser->GetHost()->SendMouseClickEvent(event, MBT_LEFT, input.getMotion() == Motion::PressedDown, 1);
                        break;
                    case Key::A:
                        m_webBrowser->GetHost()->SendKeyEvent(keyEvent);
                        break;
                    case Key::DoubleClick:
                    case Key::MiddleClick:
                    case Key::RightClick:
                    case Key::MouseExtra1:
                    case Key::MouseExtra2:
//                    case SDL_MOUSEMOTION:
//                        event.x = e.motion.x;
//                        event.y = e.motion.y;
//
//                        browser->GetHost()->SendMouseMoveEvent(event, false);
//                        break;
//
//                    case SDL_MOUSEBUTTONUP:
//                        event.x = e.button.x;
//                        event.y = e.button.y;
//
//                        browser->GetHost()->SendMouseClickEvent(event, translateMouseButton(e.button), true, 1);
//                        break;
//
//                    case SDL_MOUSEBUTTONDOWN:
//                        event.x = e.button.x;
//                        event.y = e.button.y;
//
//                        browser->GetHost()->SendMouseClickEvent(event, translateMouseButton(e.button), false, 1);
//                        break;
//
//                    case SDL_MOUSEWHEEL: {
//                        int delta_x = e.wheel.x;
//                        int delta_y = e.wheel.y;
//
//                        if (SDL_MOUSEWHEEL_FLIPPED == e.wheel.direction) {
//                            delta_y *= -1;
//                        } else {
//                            delta_x *= -1;
//                        }
//
//                        browser->GetHost()->SendMouseWheelEvent(event, delta_x, delta_y);
//                        break;
//                    }
                    default:
                        break;
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
        m_webRenderer->resize(width, height);
        m_webBrowser->GetHost()->WasResized();
    }
} // BattleRoom namespace


//
// Created by james on 1/19/19.
//
#include <third_party/cef/cef_binary_3.3396.1777.g636f29b_linux64/include/cef_browser.h>
#include "input.h"
#include "logger.h"

namespace BattleRoom {

    const int DEFAULT_KEY_CODE = 0;
    const int DEFAULT_CHAR_CODE = -1;

    using InputKey::Key;
    using InputKey::Motion;
    using InputKey::Modifier;

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

    KeyCodes getAlphabetCodes(Key key, Modifiers modifiers) {
        int diff = key - Key::A;
        return {65 + diff, (modifiers.uppercase ? 'A' : 'a') + diff};
    }

    KeyCodes getNumberRowCodes(Key key) {

        int diff = key - Key::Zero;
        int char_code = '0' + diff;

        if (key > Key::Nine) {
            diff = key - Key::Exclaim;
            switch (key) {
                case Key::Exclaim:
                    char_code = '!';
                    break;
                case Key::At:
                    char_code = '@';
                    break;
                case Key::Pound:
                    char_code = '#';
                    break;
                case Key::Dollar:
                    char_code = '$';
                    break;
                case Key::Percent:
                    char_code = '%';
                    break;
                case Key::Caret:
                    char_code = '^';
                    break;
                case Key::Ampersand:
                    char_code = '&';
                    break;
                case Key::Asterisk:
                    char_code = '*';
                    break;
                case Key::LeftParen:
                    char_code = '(';
                    break;
                case Key::RightParen:
                    char_code = ')';
                    break;
                default:
                    break;
            }
        }
        return {48 + diff, char_code};
    }

    KeyCodes getFunctionKeyCodes(Key key) {
        return {112 + (key - Key::F1), DEFAULT_CHAR_CODE};
    }

    KeyCodes getSpecialKeyCodes(Key key) {

        int key_code = DEFAULT_KEY_CODE;
        int char_code = DEFAULT_CHAR_CODE;

        switch (key) {
            case Key::Space:
                key_code = 32;
                char_code = ' ';
                break;
            case Key::Backspace:
                key_code = 8;
                break;
            case Key::Tab:
                key_code = 9;
                break;
            case Key::Return:
                key_code = 13;
                char_code = 13;
                break;
            case Key::Escape:
                key_code = 27;
                break;
            case Key::Left:
                key_code = 37;
                break;
            case Key::Up:
                key_code = 38;
                break;
            case Key::Right:
                key_code = 39;
                break;
            case Key::Down:
                key_code = 40;
                break;
            case Key::Home:
                key_code = 36;
                break;
            case Key::End:
                key_code = 35;
                break;
            case Key::PageUp:
                key_code = 33;
                break;
            case Key::PageDown:
                key_code = 34;
                break;
            case Key::Insert:
                key_code = 45;
                break;
            case Key::Delete:
                key_code = 46;
                char_code = 127;
                break;
            case Key::Divide:
                key_code = 111;
                char_code = 47;
                break;
            case Key::Multiply:
                key_code = 106;
                char_code = 42;
                break;
            case Key::Subtract:
                key_code = 109;
                char_code = 45;
                break;
            case Key::Add:
                key_code = 107;
                char_code = 43;
                break;
            case Key::Decimal:
                key_code = 110; // keyboard layout dependent!
                char_code = 46;
                break;
            case Key::Zero:
                key_code = 45;
                break;
            case Key::One:
                key_code = 35;
                break;
            case Key::Two:
                key_code = 40;
                break;
            case Key::Three:
                key_code = 34;
                break;
            case Key::Four:
                key_code = 37;
                break;
            case Key::Five:
                key_code = 12;
                break;
            case Key::Six:
                key_code = 39;
                break;
            case Key::Seven:
                key_code = 36;
                break;
            case Key::Eight:
                key_code = 38;
                break;
            case Key::Nine:
                key_code = 33;
                break;
            case Key::Semicolon:
                key_code = 186;
                char_code = ';';
                break;
            case Key::Colon:
                key_code = 186;
                char_code = ':';
                break;
            case Key::Quote:
                key_code = 222;
                char_code = '\'';
                break;
            case Key::DoubleQuote:
                key_code = 222;
                char_code = '"';
                break;
            case Key::Plus:
                key_code = 187;
                char_code = '+';
                break;
            case Key::Equals:
                key_code = 187;
                char_code = '=';
                break;
            case Key::Comma:
                key_code = 188;
                char_code = ',';
                break;
            case Key::LessThan:
                key_code = 188;
                char_code = '<';
                break;
            case Key::Minus:
                key_code = 189;
                char_code = '-';
                break;
            case Key::Underscore:
                key_code = 189;
                char_code = '_';
                break;
            case Key::Period:
                key_code = 190;
                char_code = '.';
                break;
            case Key::GreaterThan:
                key_code = 190;
                char_code = '>';
                break;
            case Key::ForwardSlash:
                key_code = 191;
                char_code = '/';
                break;
            case Key::Question:
                key_code = 191;
                char_code = '?';
                break;
            case Key::Backquote:
                key_code = 192;
                char_code = '`';
                break;
            case Key::Tilde:
                key_code = 192;
                char_code = '~';
                break;
            case Key::LeftBracket:
                key_code = 219;
                char_code = '[';
                break;
            case Key::LeftCurlyBracket:
                key_code = 219;
                char_code = '{';
                break;
            case Key::Backslash:
                key_code = 220;
                char_code = '\\';
                break;
            case Key::Pipe:
                key_code = 220;
                char_code = '|';
                break;
            case Key::RightBracket:
                key_code = 221;
                char_code = ']';
                break;
            case Key::RightCurlyBracket:
                key_code = 221;
                char_code = '}';
                break;
            default:
                break;
        }

        return {key_code, char_code};
    }

    uint32 getModifiersCode(Modifiers modifiers) {
        uint32 modifiersCode = 0;
        if (modifiers.shift) {
            modifiersCode += EVENTFLAG_SHIFT_DOWN;
        }
        if (modifiers.ctrl) {
            modifiersCode += EVENTFLAG_CONTROL_DOWN;
        }
        if (modifiers.alt) {
            modifiersCode += EVENTFLAG_ALT_DOWN;
        }
        if (modifiers.num_lock) {
            modifiersCode += EVENTFLAG_NUM_LOCK_ON;
        }
        if (modifiers.caps_lock) {
            modifiersCode += EVENTFLAG_CAPS_LOCK_ON;
        }
        return modifiersCode;
    }

    void handleMouseOnlyEvent(Input input, int x, int y, CefBrowser *browser) {
        CefMouseEvent event;
        event.x = x;
        event.y = y;

        if (input.getScrollAmount() != 0) {
            browser->GetHost()->SendMouseWheelEvent(event, 0, input.getScrollAmount());
        } else {
            browser->GetHost()->SendMouseMoveEvent(event, false);
        }
    }

    void handleMouseEvent(Input input, int x, int y, CefBrowser *browser) {
        CefMouseEvent event;
        event.x = x;
        event.y = y;

        CefBrowserHost::MouseButtonType mouseButtonType;
        int clickNum = 1;

        switch (input.getKey()) {
            case Key::MiddleClick:
                mouseButtonType = MBT_MIDDLE;
                break;
            case Key::RightClick:
                mouseButtonType = MBT_RIGHT;
                break;
            case Key::DoubleClick:
                clickNum = 2;
            case Key::LeftClick:
            case Key::MouseExtra1:
            case Key::MouseExtra2:
            default:
                mouseButtonType = MBT_LEFT;
                break;
        }

        browser->GetHost()->SendMouseClickEvent(
                event,
                mouseButtonType,
                input.getMotion() == Motion::PressedDown,
                clickNum
        );
    }

    void handleKeyEvent(Input input, CefBrowser *browser) {

        if (input.getMotion() != Motion::PressedDown && input.getMotion() != Motion::Released) {
            return;
        }

        /** Output codes **/
        KeyCodes keyCodes(0, -1);
        Key key = input.getKey();
        Modifiers modifiers = input.getModifiers();

        if (key >= Key::A && key <= Key::Z) {
            keyCodes = getAlphabetCodes(key, modifiers);
        } else if (key >= Key::Zero && key <= Key::LeftParen) {
            keyCodes = getNumberRowCodes(key);

            /** Function Keys **/
        } else if (key >= Key::F1 && key <= Key::F12) {
            keyCodes = getFunctionKeyCodes(key);

        } else {
            /** Special Keys **/
            keyCodes = getSpecialKeyCodes(key);
        }

        /** Still not mapped? **/
        if (keyCodes.key_code == 0) {
            Log::warn("Unmapped key");
        }

        /** Fire key events to CEF **/
        if (input.getMotion() == Motion::PressedDown) {

            // onkeydown
            CefKeyEvent key_event_key_down;
            key_event_key_down.type = KEYEVENT_KEYDOWN;
            key_event_key_down.modifiers = getModifiersCode(modifiers);
            key_event_key_down.windows_key_code = keyCodes.key_code;
            key_event_key_down.native_key_code = keyCodes.key_code;
            key_event_key_down.character = keyCodes.getChar16();
            key_event_key_down.unmodified_character = keyCodes.getChar16();
            browser->GetHost()->SendKeyEvent(key_event_key_down);
            // Fire a second key event for characters only
            if (keyCodes.char_code >= 0) {
                // onkeypress
                CefKeyEvent key_event_char;
                key_event_char.type = KEYEVENT_CHAR;
                key_event_char.modifiers = getModifiersCode(modifiers);
                key_event_char.windows_key_code = keyCodes.key_code;
                key_event_char.native_key_code = keyCodes.key_code;
                key_event_char.character = keyCodes.getChar16();
                key_event_char.unmodified_character = keyCodes.getChar16();
                browser->GetHost()->SendKeyEvent(key_event_char);
            }
        } else if (input.getMotion() == Motion::Released) {
            // onkeyup
            CefKeyEvent key_event_key_up;
            key_event_key_up.type = KEYEVENT_KEYUP;
            key_event_key_up.modifiers = getModifiersCode(modifiers);
            key_event_key_up.windows_key_code = keyCodes.key_code;
            key_event_key_up.native_key_code = keyCodes.key_code;
            key_event_key_up.character = keyCodes.getChar16();
            key_event_key_up.unmodified_character = keyCodes.getChar16();
            browser->GetHost()->SendKeyEvent(key_event_key_up);
        }
    }

    void cefHandleInput(Input input, int x, int y, CefBrowser *browser) {

        switch (input.getKey()) {

            case InputKey::MouseOnly:
                handleMouseOnlyEvent(input, x, y, browser);
                break;
            case InputKey::LeftClick:
            case InputKey::DoubleClick:
            case InputKey::MiddleClick:
            case InputKey::RightClick:
            case InputKey::MouseExtra1:
            case InputKey::MouseExtra2:
                handleMouseEvent(input, x, y, browser);
                break;
            default:
                handleKeyEvent(input, browser);
                break;
        }
    }
} // BattleRoom namespace

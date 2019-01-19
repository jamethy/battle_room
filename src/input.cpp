#include "input.h"

namespace BattleRoom {

    Input::Input() {
        m_viewIntersections.clear();
        m_viewRelIntersections.clear();
    }

    bool Input::containsView(UniqueId viewId) {
        return m_viewIntersections.count(viewId) != 0;
    }

    void Input::addViewIntersection(UniqueId viewId, Vector3D intersection) {
        m_viewIntersections.insert(std::pair<UniqueId, Vector3D>(viewId, intersection));
    }

    void Input::addViewIntersection(UniqueId viewId, RelPixel intersection) {
        m_viewRelIntersections.insert(std::pair<UniqueId, RelPixel>(viewId, intersection));
    }

    Vector3D Input::getViewIntersection(UniqueId viewId) {
        if (containsView(viewId)) {
            return m_viewIntersections.at(viewId);
        }
        return Vector3D(0, 0, -1);
    }

    RelPixel Input::getViewRelIntersection(UniqueId viewId) {
        if (containsView(viewId)) {
            return m_viewRelIntersections.at(viewId);
        }
        return RelPixel(-1, -1);
    }

    bool Input::isKeyDown(InputKey::Key k) {
        return k == m_key
               && InputKey::Motion::PressedDown == m_keyMotion
               && m_modifiers.isPlain();
    }

    bool Input::isKeyUp(InputKey::Key k) {
        return k == m_key
               && InputKey::Motion::Released == m_keyMotion
               && m_modifiers.isPlain();
    }

    bool Input::isModKeyDown(InputKey::Modifier mod, InputKey::Key k) {
        bool keyDown = k == m_key && InputKey::Motion::PressedDown == m_keyMotion;
        if (!keyDown) {
            return false;
        } else {
            switch (mod) {
                case InputKey::Plain:
                    return m_modifiers.isPlain();
                case InputKey::Shift:
                    return m_modifiers.shift;
                case InputKey::Ctrl:
                    return m_modifiers.ctrl;
                case InputKey::Alt:
                    return m_modifiers.alt;
                default:
                    return false;
            }
        }
    }

    bool Input::isModKeyUp(InputKey::Modifier mod, InputKey::Key k) {
        bool keyUp = k == m_key && InputKey::Motion::Released == m_keyMotion;
        if (keyUp) {
            return true;
        } else {
            switch (mod) {
                case InputKey::Plain:
                    return !m_modifiers.isPlain();
                case InputKey::Shift:
                    return !m_modifiers.shift;
                case InputKey::Ctrl:
                    return !m_modifiers.ctrl;
                case InputKey::Alt:
                    return !m_modifiers.alt;
                default:
                    return false;
            }
        }
    }

// setters and getters

    void Input::setKey(InputKey::Key key) {
        m_key = key;
    }

    void Input::setMotion(InputKey::Motion motion) {
        m_keyMotion = motion;
    }

    void Input::setScrollAmount(int amount) {
        m_scrollAmount = amount;
    }

    void Input::setModifiers(Modifiers modifiers) {
        m_modifiers = modifiers;
    }

    InputKey::Key Input::getKey() {
        return m_key;
    }

    InputKey::Motion Input::getMotion() {
        return m_keyMotion;
    }

    int Input::getScrollAmount() {
        return m_scrollAmount;
    }

    Modifiers Input::getModifiers() {
        return m_modifiers;
    }

    bool Modifiers::isPlain() {
        return !shift && !ctrl && !alt;
    }
} // BattleRoom namespace

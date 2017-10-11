#include "battle_room/common/input.h"

using std::string;

namespace BattleRoom {

    bool Input::containsView(string viewName) {
        return m_viewIntersections.count(viewName) != 0;
    }

    void Input::addViewIntersection(string viewName, Vector3D intersection) {
        m_viewIntersections.insert(std::pair<string, Vector3D>(viewName, intersection));
    }

    Vector3D Input::getViewIntersection(string viewName) {
        if (containsView(viewName)) {
            return m_viewIntersections.at(viewName);
        }
        return Vector3D(0, 0, -1);
    }

    bool Input::isKeyDown(InputKey::Key k) {
        return k == m_key 
            && InputKey::Motion::PressedDown == m_keyMotion
            && InputKey::Modifier::Plain == m_modifier;
    }

    bool Input::isKeyUp(InputKey::Key k) {
        return k == m_key 
            && InputKey::Motion::Released == m_keyMotion
            && InputKey::Modifier::Plain == m_modifier;
    }

    bool Input::isModKeyDown(InputKey::Modifier mod, InputKey::Key k) {
        return mod == m_modifier 
            && k == m_key 
            && InputKey::Motion::PressedDown == m_keyMotion;
    }

    bool Input::isModKeyUp(InputKey::Modifier mod, InputKey::Key k) {
        return mod == m_modifier 
            && k == m_key 
            && InputKey::Motion::Released == m_keyMotion;
    }

// setters and getters

    void Input::setKey(InputKey::Key key) {
        m_key = key;
    }

    void Input::setMotion(InputKey::Motion motion) {
        m_keyMotion = motion;
    }

    void Input::setModifier(InputKey::Modifier modifier) {
        m_modifier = modifier;
    }

    void Input::setScrollAmount(int amount) {
        m_scrollAmount = amount;
    }

    InputKey::Key Input::getKey() {
        return m_key;
    }

    InputKey::Motion Input::getMotion() {
        return m_keyMotion;
    }

    InputKey::Modifier Input::getModifier() {
        return m_modifier;
    }

    int Input::getScrollAmount() {
        return m_scrollAmount;
    }

} // BattleRoom namespace

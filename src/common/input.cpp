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

    InputKey::Key Input::getKey() {
        return m_key;
    }

    InputKey::Motion Input::getMotion() {
        return m_keyMotion;
    }

    int Input::getScrollAmount() {
        return m_scrollAmount;
    }

} // BattleRoom namespace

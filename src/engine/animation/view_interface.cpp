#include "battle_room/engine/animation/view_interface.h"

namespace BattleRoom {

std::string ViewInterface::getAssociatedView() const {
    return m_associatedView;
}

void ViewInterface::setAssociatedView(std::string viewName) {
    m_associatedView = viewName;
}

} // BattleRoom namespace

#include "battle_room/common/view_interface.h"

namespace BattleRoom {

    void ViewInterface::applySettings(ResourceDescriptor settings) {

        if (isNotEmpty(settings.getValue())) {
            setAssociatedView(settings.getValue());
        }

    }

    std::string ViewInterface::getAssociatedView() const {
        return m_associatedView;
    }

    void ViewInterface::setAssociatedView(std::string viewName) {
        m_associatedView = viewName;
    }

} // BattleRoom namespace

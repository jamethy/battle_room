#include "battle_room/common/view_interface.h"

namespace BattleRoom {

    ViewInterface::ViewInterface() : m_uniqueId(UniqueId::generateNewLocalId()) {}

    void ViewInterface::applySettings(ResourceDescriptor settings) {

        if (isNotEmpty(settings.getValue())) {
            setAssociatedView(settings.getValue());
        }

    }

    std::string ViewInterface::getAssociatedView() const {
        return m_associatedView;
    }

    const UniqueId ViewInterface::getUniqueId() const {
        return m_uniqueId;
    }

    void ViewInterface::setAssociatedView(std::string viewName) {
        m_associatedView = viewName;
    }

} // BattleRoom namespace

#include "battle_room/common/view_interface.h"

namespace BattleRoom {

    ViewInterface::ViewInterface(UniqueId associatedView) : 
        m_associatedView(associatedView),
        m_uniqueId(associatedView) {}

    void ViewInterface::applySettings(ResourceDescriptor settings) {
        (void)settings;
    }

    UniqueId ViewInterface::getAssociatedView() const {
        return m_associatedView;
    }

    const UniqueId ViewInterface::getUniqueId() const {
        return m_uniqueId;
    }

} // BattleRoom namespace

#include "views/game_ui_element.h"

namespace BattleRoom {

    GameUIElement::GameUIElement() : m_uniqueId(UniqueId::generateNewLocalId()) {
    }

// getters and setters

    UniqueId GameUIElement::getUniqueId() const {
        return m_uniqueId;
    }

    Vector3D GameUIElement::getLocation() const {
        return m_location;
    }

    void GameUIElement::setLocation(const Vector3D &location) {
        m_location = location;
    }

    void GameUIElement::applySettings(ResourceDescriptor settings) {
        (void)settings;
    }

    ResourceDescriptor GameUIElement::getSettings() const {
        ResourceDescriptor rd("GameUIElement", getType());
        rd.emplaceSubResource("type", getType());
        return rd;
    }

}// BattleRoom namespace


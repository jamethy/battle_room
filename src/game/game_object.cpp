#include "battle_room/game/game_object.h"

namespace BattleRoom {

// apply settings

void GameObject::applySettings(ResourceDescriptor settings) {
    
    DrawableObject::applySettings(settings);

}

// constructor

GameObject::GameObject(UniqueId uniqueId) 
    : m_uniqueId(uniqueId)
{ }

// getters and setters

const UniqueId GameObject::getUniqueId() const {
    return m_uniqueId;
}

} // BattleRoom namespace

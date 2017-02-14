#include "battle_room/game/game_object.h"

namespace BattleRoom {

// apply settings

void GameObject::applySettings(ResourceDescriptor settings) {
    
    DrawableObject::applySettings(settings);

    m_velocity.applySettings( settings.getSubResource("Velocity") );

    ResourceDescriptor sub = settings.getSubResource("Static");
    if (isNotEmpty(sub.getValue())) {
        m_isStatic = keyMatch("True",sub.getValue());
    }

}

// constructor

GameObject::GameObject(UniqueId uniqueId) 
    : m_uniqueId(uniqueId),
    m_isStatic(false)
{ }

// getters and setters

const UniqueId GameObject::getUniqueId() const {
    return m_uniqueId;
}

Vector3D GameObject::getVelocity() {
    return m_velocity;
}

bool GameObject::isStatic() const {
    return m_isStatic;
}

void GameObject::setIsStatic(bool isStatic) {
    m_isStatic = isStatic;
}

} // BattleRoom namespace

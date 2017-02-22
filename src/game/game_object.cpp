#include "battle_room/game/game_object.h"

namespace BattleRoom {

// apply settings

void GameObject::applySettings(ResourceDescriptor settings) {

    setName(settings.getValue());
    DrawableObject::applySettings(settings);

    m_velocity.applySettings( settings.getSubResource("Velocity") );

    ResourceDescriptor sub = settings.getSubResource("Static");
    if (isNotEmpty(sub.getValue())) {
        setIsStatic(keyMatch("True",sub.getValue()));
    }

    sub = settings.getSubResource("Mass");
    if (isNotEmpty(sub.getValue())) {
        setMass(toKilograms(sub.getValue()));
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

kilograms GameObject::getMass() const {
    return m_mass;
}

bool GameObject::isStatic() const {
    return m_isStatic;
}

std::string GameObject::getName() const {
    return m_name;
}

void GameObject::setIsStatic(bool isStatic) {
    m_isStatic = isStatic;
}

void GameObject::setVelocity(Vector3D velocity) {
    m_velocity = velocity;
}

void GameObject::setMass(kilograms mass) {
    if (mass >= 0) {
        m_mass = mass;
    }
}

void GameObject::setName(std::string name) {
    m_name = name;
}
} // BattleRoom namespace

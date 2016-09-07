#include "battle_room/common/object.h"
#include "battle_room/engine/animation/animation_handler.h"

namespace BattleRoom {

// apply settings

void Object::applySettings(ResourceDescriptor settings) {

    m_location.applySettings( settings.getSubResource("Location") );
    m_orientation.applySettings( settings.getSubResource("Orientation") );

    ResourceDescriptor sub = settings.getSubResource("Animation");
    if (isNotEmpty(sub.getValue())) {
        setAnimation(AnimationHandler::getAnimation(sub.getValue()));
    }

    sub = settings.getSubResource("AnimationState");
    if (isNotEmpty(sub.getValue())) {
        setAnimationState(toSeconds(sub.getValue()));
    }
}

// Constructor

Object::Object(UniqueId id) : 
    m_id(id),
    m_currentAnimation(AnimationHandler::getAnimation(MISSING_ANIMATION)),
    m_animationState(0)
{}

// getters and setters

Animation& Object::getAnimation() const {
    return m_currentAnimation;
}

seconds Object::getAnimationState() const {
    return m_animationState;
}

Vector3D Object::getLocation() const {
    return m_location;
}

Quaternion Object::getOrientation() const {
    return m_orientation;
}

UniqueId Object::getUniqueId() const {
    return m_id;
}

void Object::setAnimation(Animation animation) {
    m_currentAnimation = animation;
}

void Object::setAnimationState(seconds animationState) {
    m_animationState = animationState;
}

void Object::setLocation(Vector3D location) {
     m_location = location;
}

void Object::setOrientation(Quaternion orientation) {
    m_orientation = orientation;
}

} // BattleRoom namespace

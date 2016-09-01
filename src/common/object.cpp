#include "battle_room/common/object.h"
#include "battle_room/engine/animation/animation_handler.h"

namespace BattleRoom {

// apply settings

void Object::applySettings(ResourceDescriptor settings) {

    ResourceDescriptor sub = settings.getSubResource("Animation");
    if (!sub.getKey().empty()) {
        setAnimation(AnimationHandler::getAnimation(sub.getValue()));
    }

    sub = settings.getSubResource("AnimationState");
    if (!sub.getKey().empty()) {
        setAnimationState(toSeconds(sub.getValue()));
    }

    sub = settings.getSubResource("Position");
    if (!sub.getKey().empty()) {
        position().applySettings(sub);
    }
}

// Constructor

Object::Object(UniqueId id) : 
    m_id(id),
    m_currentAnimation(AnimationHandler::getAnimation(MISSING_ANIMATION)),
    m_animationState(0)
{}

// reference accessor functions

Position& Object::position() {
    return m_position;
}

// getters and setters

Animation& Object::getAnimation() const {
    return m_currentAnimation;
}

seconds Object::getAnimationState() const {
    return m_animationState;
}

Position Object::getPosition() const {
    return m_position;
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

void Object::setPosition(Position pos) {
    m_position = pos;
}

} // BattleRoom namespace

#include "battle_room/common/object.h"
#include "battle_room/engine/animation/animation_handler.h"

namespace BattleRoom {

// Constructor

Object::Object() : 
    m_currentAnimation(AnimationHandler::get().getAnimation(MISSING_ANIMATION)),
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

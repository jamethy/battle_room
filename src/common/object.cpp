#include "battle_room/common/object.h"
#include "battle_room/engine/animation/animation_handler.h"

namespace BattleRoom {

Object::Object() : 
    m_currentAnimation(AnimationHandler::get().getAnimation(MISSING_ANIMATION)),
    m_animationState(0)
{}

Animation& Object::getAnimation() const {
    return m_currentAnimation;
}

void Object::setAnimation(Animation animation) {
    m_currentAnimation = animation;
}

seconds Object::getAnimationState() const {
    return m_animationState;
}

void Object::setAnimationState(seconds animationState) {
    m_animationState = animationState;
}

Position& Object::position() {
    return m_position;
}

Position Object::getPosition() const {
    return m_position;
}

void Object::setPosition(Position pos) {
    m_position = pos;
}

} // BattleRoom namespace

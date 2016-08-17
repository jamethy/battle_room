#include "battle_room/common/object.h"
#include "battle_room/engine/animation/animation_handler.h"

namespace BattleRoom {

Object::Object() : 
    m_currentAnimation(AnimationHandler::get().getAnimation(MISSING_ANIMATION)),
    m_animationState(0)
{}

Animation Object::getAnimation() {
    return m_currentAnimation;
}

void Object::setAnimation(Animation animation) {
    m_currentAnimation = animation;
}

seconds Object::getAnimationState() {
    return m_animationState;
}

void Object::setAnimationState(seconds animationState) {
    m_animationState = animationState;
}

Position Object::getPosition() {
    return m_pos;
}

void Object::setPosition(Position pos) {
    m_pos = pos;
}

Orientation Object::getOrientation() {
    return m_orientation;
}

void Object::setOrientation(Orientation orientation) {
    m_orientation = orientation;
}

} // BattleRoom namespace

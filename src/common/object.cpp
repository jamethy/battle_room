#include "battle_room/common/object.h"

namespace BattleRoom {

Object::Object() : 
    m_currentAnimation(Animation::getDefaultAnimation()), 
    m_animationState(0)
{}

Animation getAnimation() {
    return m_currentAnimation;
}

void setAnimation(Animation animation) {
    m_currentAnimation = animation;
}

seconds getAnimationState() {
    return m_animationState;
}

void setAnimationState(seconds animationState) {
    m_animationState = animationState;
}

} // BattleRoom namespace

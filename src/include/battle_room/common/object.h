#ifndef OBJECT_H
#define OBJECT_H

#include "battle_room/engine/animation/animation.h"

namespace Common {

// TODO fill class
class Object {

public:

    Animation::Animation getAnimation();
    void setAnimation(Animation::Animation animation);

    Animation::seconds getAnimationState();
    void setAnimationState(Animation::seconds animationState);

    Object();

private:

    Animation::Animation& m_currentAnimation;
    Animation::seconds m_animationState;
    // point in animation
    // position

}; // Object class
} // Common namespace
#endif // OBJECT_H

#ifndef OBJECT_H
#define OBJECT_H

#include "battle_room/engine/animation/animation.h"

namespace BattleRoom {

// TODO fill class
class Object {

public:

    Animation getAnimation();
    void setAnimation(Animation animation);

    seconds getAnimationState();
    void setAnimationState(seconds animationState);

    Object();

private:

    Animation& m_currentAnimation;
    seconds m_animationState;
    // point in animation
    // position

}; // Object class
} // BattleRoom namespace
#endif // OBJECT_H

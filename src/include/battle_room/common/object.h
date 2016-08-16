#ifndef OBJECT_H
#define OBJECT_H

#include "battle_room/engine/animation/animation.h"
#include "battle_room/common/position.h"

namespace BattleRoom {

// TODO fill class
class Object {

public:

    Animation getAnimation();
    seconds getAnimationState();
    Position getPosition();

    void setAnimationState(seconds animationState);
    void setAnimation(Animation animation);
    void setPosition(Position pos);

    Object();

private:

    Animation& m_currentAnimation;
    seconds m_animationState;
    // point in animation
    Position m_pos;

}; // Object class
} // BattleRoom namespace
#endif // OBJECT_H

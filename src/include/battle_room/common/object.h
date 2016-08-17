#ifndef OBJECT_H
#define OBJECT_H

#include "battle_room/engine/animation/animation.h"
#include "battle_room/common/position.h"

namespace BattleRoom {

class Object {

public:

    Animation getAnimation();
    seconds getAnimationState();
    Position getPosition();

    void setAnimation(Animation animation);
    void setAnimationState(seconds animationState);
    void setPosition(Position pos);
    
    Object();

    Position& position();

private:

    Animation& m_currentAnimation;
    seconds m_animationState;
    Position m_position;

}; // Object class
} // BattleRoom namespace
#endif // OBJECT_H

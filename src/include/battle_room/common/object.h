#ifndef OBJECT_H
#define OBJECT_H

#include "battle_room/engine/animation/animation.h"
#include "battle_room/common/position.h"
#include "battle_room/common/orientation.h"

namespace BattleRoom {

class Object {

public:

    Animation getAnimation();
    seconds getAnimationState();
    Position getPosition();
    Orientation getOrientation();

    void setAnimationState(seconds animationState);
    void setAnimation(Animation animation);
    void setPosition(Position pos);
    void setOrientation(Orientation orientation);
    
    Object();

private:

    Animation& m_currentAnimation;
    seconds m_animationState;
    Position m_pos;
    Orientation m_orientation;

}; // Object class
} // BattleRoom namespace
#endif // OBJECT_H

#ifndef OBJECT_H
#define OBJECT_H

#include "battle_room/engine/animation/animation.h"
#include "battle_room/common/position.h"

namespace BattleRoom {

class Object {

public:

    Animation& getAnimation() const;
    seconds getAnimationState() const;
    Position getPosition() const;

    void setAnimation(Animation animation);
    void setAnimationState(seconds animationState);
    void setPosition(Position pos);
    
    Object();

    Position& position();

    //TODO figure out how to get rid of this
    Object& operator=(const Object& other) {
        m_currentAnimation = other.m_currentAnimation;
        m_animationState = other.m_animationState;
        m_position = other.m_position;
        return *this;
    }

private:

    Animation& m_currentAnimation;
    seconds m_animationState;
    Position m_position;

}; // Object class
} // BattleRoom namespace
#endif // OBJECT_H

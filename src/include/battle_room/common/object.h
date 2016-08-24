#ifndef OBJECT_H
#define OBJECT_H

#include "battle_room/engine/animation/animation.h"
#include "battle_room/common/position.h"

namespace BattleRoom {

/**
 * \brief Object that is drawabled on a view
 */
class Object {

public:

    // Constructor
    Object();

    // Reference accessor functions
    Position& position();

    // getters and setters

    Animation& getAnimation() const;
    seconds getAnimationState() const;
    Position getPosition() const;

    void setAnimation(Animation animation);
    void setAnimationState(seconds animationState);
    void setPosition(Position pos);

    //TODO figure out how to get rid of this
    Object& operator=(const Object& other) {
        m_currentAnimation = other.m_currentAnimation;
        m_animationState = other.m_animationState;
        m_position = other.m_position;
        return *this;
    }

private:

    Animation& m_currentAnimation; ///< Animation object is on
    seconds m_animationState; ///< Seconds into animation
    Position m_position; ///< Location and Orientation of object

}; // Object class
} // BattleRoom namespace
#endif // OBJECT_H

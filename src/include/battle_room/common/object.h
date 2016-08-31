#ifndef OBJECT_H
#define OBJECT_H


#include "battle_room/common/unique_id.h"
#include "battle_room/common/resource.h"
#include "battle_room/common/position.h"
#include "battle_room/engine/animation/animation.h"

namespace BattleRoom {

/**
 * \brief Object that is drawabled on a view
 */
class Object : public Resource {

public:

    // Constructor
    Object(UniqueId id);

    // Reference accessor functions
    Position& position();

    // getters and setters

    Animation& getAnimation() const;
    seconds getAnimationState() const;
    Position getPosition() const;
    UniqueId getUniqueId() const;

    void setAnimation(Animation animation);
    void setAnimationState(seconds animationState);
    void setPosition(Position pos);

    // inherited
    virtual void applySettings(ResourceDescriptor settings) override;

    //TODO figure out how to get rid of this
    Object& operator=(const Object& other) {
        m_currentAnimation = other.m_currentAnimation;
        m_animationState = other.m_animationState;
        m_position = other.m_position;
        return *this;
    }

private:

    UniqueId m_id; ///< Id that is unique to the object (not instance)
    Animation& m_currentAnimation; ///< Animation object is on
    seconds m_animationState; ///< Seconds into animation
    Position m_position; ///< Location and Orientation of object

}; // Object class
} // BattleRoom namespace
#endif // OBJECT_H

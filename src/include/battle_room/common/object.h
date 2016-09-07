#ifndef OBJECT_H
#define OBJECT_H

#include "battle_room/common/unique_id.h"
#include "battle_room/common/resource.h"
#include "battle_room/common/vector3d.h"
#include "battle_room/common/quaternion.h"
#include "battle_room/engine/animation/animation.h"

namespace BattleRoom {

/**
 * \brief Object that is drawabled on a view
 */
class Object : public Resource {

public:

    // Constructor
    Object(UniqueId id);

    // getters and setters

    Animation& getAnimation() const;
    seconds getAnimationState() const;
    Vector3D getLocation() const;
    Quaternion getOrientation() const;
    UniqueId getUniqueId() const;

    void setAnimation(Animation animation);
    void setAnimationState(seconds animationState);
    void setLocation(Vector3D location);
    void setOrientation(Quaternion orientation);

    // inherited
    virtual void applySettings(ResourceDescriptor settings) override;

    //TODO figure out how to get rid of this
    Object& operator=(const Object& other) {
        m_currentAnimation = other.m_currentAnimation;
        m_animationState = other.m_animationState;
        m_location = other.m_location;
        m_orientation = other.m_orientation;
        return *this;
    }

private:

    UniqueId m_id; ///< Id that is unique to the object (not instance)
    Animation& m_currentAnimation; ///< Animation object is on
    seconds m_animationState; ///< Seconds into animation
    Vector3D m_location; ///< Location of the object in 3D space
    Quaternion m_orientation; ///< Orientationof the object in 3D space

}; // Object class
} // BattleRoom namespace
#endif // OBJECT_H

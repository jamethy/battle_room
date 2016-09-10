#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include "battle_room/common/resource.h"
#include "battle_room/common/vector3d.h"
#include "battle_room/common/quaternion.h"
#include "battle_room/engine/animation/animation.h"

namespace BattleRoom {

/**
 * \brief Object that is drawabled on a view
 */
class DrawableObject : public Resource {

public:

    // constructor
    DrawableObject();

    // getters and setters

    Animation& getAnimation() const;
    seconds getAnimationState() const;
    Vector3D getLocation() const;
    Quaternion getOrientation() const;

    void setAnimation(Animation animation);
    void setAnimationState(seconds animationState);
    void setLocation(Vector3D location);
    void setOrientation(Quaternion orientation);

    // inherited
    virtual void applySettings(ResourceDescriptor settings) override;

    //TODO figure out how to get rid of this
    DrawableObject& operator=(const DrawableObject& other) {
        m_currentAnimation = other.m_currentAnimation;
        m_animationState = other.m_animationState;
        m_location = other.m_location;
        m_orientation = other.m_orientation;
        return *this;
    }

private:

    Animation& m_currentAnimation; ///< Animation object is on
    seconds m_animationState; ///< Seconds into animation
    Vector3D m_location; ///< Location of the object in 3D space
    Quaternion m_orientation; ///< Orientationof the object in 3D space

}; // DrawableObject class
} // BattleRoom namespace
#endif // DRAWABLE_OBJECT_H

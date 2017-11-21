#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include "battle_room/common/resource.h"
#include "battle_room/common/vector3d.h"
#include "battle_room/common/quaternion.h"
#include "battle_room/common/animation.h"

#include <memory>

namespace BattleRoom {

/**
 * \brief Object that is drawable on a view
 */
    class DrawableObject : public Resource {

    public:

        // constructor
        DrawableObject();
        ~DrawableObject() {}

        // getters and setters

        Animation &getAnimation() const;

        seconds getAnimationState() const;

        Vector3D getLocation() const;

        Quaternion getOrientation() const;

        void setAnimation(Animation &animation);

        void setAnimationState(seconds animationState);

        void setLocation(Vector3D location);

        void setOrientation(Quaternion orientation);

        // inherited
        virtual void applySettings(ResourceDescriptor settings) override;
        void serialize(BinaryStream& bs) const;
        static DrawableObject deserialize(BinaryStream& bs);

    private:

        Animation *m_currentAnimation; ///< Animation object is on
        seconds m_animationState; ///< Seconds into animation
        Vector3D m_location; ///< Location of the object in 3D space
        Quaternion m_orientation; ///< Orientationof the object in 3D space

    }; // DrawableObject class

    typedef std::unique_ptr<DrawableObject> UniqueDrawableObject;

} // BattleRoom namespace
#endif // DRAWABLE_OBJECT_H

#ifndef BATTLE_ROOM_DRAWABLE_OBJECT_H
#define BATTLE_ROOM_DRAWABLE_OBJECT_H

#include "common/resource.h"
#include "common/vector3d.h"
#include "common/quaternion.h"
#include "animation/animation.h"

#include <memory>

namespace BattleRoom {

/**
 * \brief Object that is drawable on a view
 */
    class DrawableObject : public Resource {

    public:

        // constructor
        DrawableObject();

        ~DrawableObject() override = default;

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
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        virtual void serialize(BinaryStream &bs) const;

        static DrawableObject deserialize(BinaryStream &bs);

    private:

        Animation *m_currentAnimation; ///< Animation object is on
        seconds m_animationState; ///< Seconds into animation
        Vector3D m_location; ///< Location of the object in 3D space
        Quaternion m_orientation; ///< Orientation of the object in 3D space

    }; // DrawableObject class

    typedef std::unique_ptr<DrawableObject> UniqueDrawableObject;

} // BattleRoom namespace
#endif // BATTLE_ROOM_DRAWABLE_OBJECT_H

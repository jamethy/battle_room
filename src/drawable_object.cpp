#include "drawable_object.h"
#include "animation_handler.h"

namespace BattleRoom {

// apply settings

    void DrawableObject::applySettings(ResourceDescriptor settings) {

        m_location.applySettings(settings.getSubResource("Location"));
        m_orientation.applySettings(settings.getSubResource("Orientation"));

        ResourceDescriptor sub = settings.getSubResource("Animation");
        if (isNotEmpty(sub.getValue())) {
            setAnimation(AnimationHandler::getAnimation(sub.getValue()));
        }

        sub = settings.getSubResource("AnimationState");
        if (isNotEmpty(sub.getValue())) {
            setAnimationState(toSeconds(sub.getValue()));
        }

        sub = settings.getSubResource("Rotation");
        if (isNotEmpty(sub.getValue())) {
            m_orientation = Quaternion();
            m_orientation.rotateAboutZ(toRadians(sub.getValue()));
        }

        sub = settings.getSubResource("DegRotation");
        if (isNotEmpty(sub.getValue())) {
            radians angle = toRadians(toDegrees(sub.getValue()));
            m_orientation = Quaternion();
            m_orientation.rotateAboutZ(angle);
        }
    }

// Constructor

    DrawableObject::DrawableObject() :
            m_currentAnimation(&AnimationHandler::getAnimation(MISSING_ANIMATION)),
            m_animationState(0) {}

// getters and setters

    Animation &DrawableObject::getAnimation() const {
        return *m_currentAnimation;
    }

    seconds DrawableObject::getAnimationState() const {
        return m_animationState;
    }

    Vector3D DrawableObject::getLocation() const {
        return m_location;
    }

    Quaternion DrawableObject::getOrientation() const {
        return m_orientation;
    }

    void DrawableObject::setAnimation(Animation &animation) {
        m_currentAnimation = &animation;
    }

    void DrawableObject::setAnimationState(seconds animationState) {
        m_animationState = animationState;
    }

    void DrawableObject::setLocation(Vector3D location) {
        m_location = location;
    }

    void DrawableObject::setOrientation(Quaternion orientation) {
        m_orientation = orientation;
    }

    void DrawableObject::serialize(BinaryStream& bs) const {
        bs.writeString(m_currentAnimation->getName());
        bs.writeSeconds(m_animationState);
        m_location.serialize(bs);
        m_orientation.serialize(bs);
    }

    DrawableObject DrawableObject::deserialize(BinaryStream& bs) {
        DrawableObject obj;
        obj.m_currentAnimation = &AnimationHandler::getAnimation(bs.readString());
        obj.m_animationState = bs.readSeconds();
        obj.m_location = Vector3D::deserialize(bs);
        obj.m_orientation = Quaternion::deserialize(bs);
        return obj;
    }


} // BattleRoom namespace

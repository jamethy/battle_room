#include <src/include/battle_room/common/animation_handler.h>
#include "battle_room/game/game_object.h"

#include <iostream>
#include <cmath>

namespace BattleRoom {

// apply settings

    void GameObject::applySettings(ResourceDescriptor settings) {

        setName(settings.getValue());
        DrawableObject::applySettings(settings);

        m_position.applySettings(settings.getSubResource("Location"));
        m_velocity.applySettings(settings.getSubResource("Velocity"));

        ResourceDescriptor sub = settings.getSubResource("Rotation");
        if (isNotEmpty(sub.getValue())) {
            m_rotation = toRadians(sub.getValue());
        }

        sub = settings.getSubResource("DegRotation");
        if (isNotEmpty(sub.getValue())) {
            m_rotation  = toRadians(toDegrees(sub.getValue()));
        }

        sub = settings.getSubResource("Static");
        if (isNotEmpty(sub.getValue())) {
            setIsStatic(keyMatch("True", sub.getValue()));
        }

        sub = settings.getSubResource("Mass");
        if (isNotEmpty(sub.getValue())) {
            setMass(toKilograms(sub.getValue()));
        }
    }

// constructors

    GameObject::GameObject(UniqueId uniqueId, ObjectType type)
            : m_uniqueId(uniqueId),
              m_position(Vector2D(0,0)),
              m_rotation(0),
              m_angularVelocity(0.0),
              m_isStatic(false),
              m_destroy(false),
              m_type(type) {}

// other functinos
    void GameObject::reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal) {
        (void) intersectionNormal; // unused
        setVelocity(velocityResult);
    }

    void GameObject::updateAnimation(seconds timestep) {

        Animation &animation = getAnimation();
        seconds newState = getAnimationState() + timestep;

        if (newState > animation.getLength()) {

            // set the new state (time elapsed since end of last animation)
            setAnimationState(newState - animation.getLength());

            // find the new animation
            animation = AnimationHandler::getAnimation(animation.getNextAnimation());
        } else {

            // iterate object->animation
            setAnimationState(newState);
        }

    }

    void GameObject::setUp(Vector2D up) {
        setRotation(atan2(-up.x(), up.y()));
    }

// getters and setters

    const UniqueId GameObject::getUniqueId() const {
        return m_uniqueId;
    }

    Vector2D GameObject::getPosition() {
        return m_position;
    }

    radians GameObject::getRotation() const {
        return m_rotation;
    }

    Vector2D GameObject::getVelocity() {
        return m_velocity;
    }

    double GameObject::getAngularVelocity() const {
        return m_angularVelocity;
    }

    kilograms GameObject::getMass() const {
        return m_mass;
    }

    bool GameObject::isStatic() const {
        return m_isStatic;
    }

    bool GameObject::destroy() const {
        return m_destroy;
    }

    std::string GameObject::getName() const {
        return m_name;
    }

    ObjectType GameObject::getType() const {
        return m_type;
    }

    void GameObject::setPosition(Vector2D position) {
        m_position = position;
        setLocation(Vector3D(position.x(), position.y(), 0));
    }

    void GameObject::setRotation(radians rotation) {
        m_rotation = rotation;
        setOrientation(Quaternion(rotation));
    }

    void GameObject::setIsStatic(bool isStatic) {
        m_isStatic = isStatic;
    }

    void GameObject::setToDestroy(bool destroy) {
        m_destroy = destroy;
    }

    void GameObject::setVelocity(Vector2D velocity) {
        m_velocity = velocity;
    }

    void GameObject::setAngularVelocity(double radiansPerSecond) {
        m_angularVelocity = radiansPerSecond;
    }

    void GameObject::setMass(kilograms mass) {
        if (mass >= 0) {
            m_mass = mass;
        }
    }

    void GameObject::setName(std::string name) {
        m_name = name;
    }
} // BattleRoom namespace

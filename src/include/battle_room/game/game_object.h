#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "battle_room/common/drawable_object.h"
#include "battle_room/common/vector2d.h"
#include "battle_room/common/unique_id.h"
#include "battle_room/game/objects/object_type.h"

namespace BattleRoom {

    class GameObject : public DrawableObject {

    public:

        // constructor
        GameObject(UniqueId uniqueId, ObjectType type);

        virtual void reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal);

        virtual void updateAnimation(seconds timestep);

        void setUp(Vector2D up);

        // getters and setters

        const UniqueId getUniqueId() const;

        Vector2D getPosition();

        radians getRotation() const;

        Vector2D getVelocity();

        double getAngularVelocity() const;

        bool isStatic() const;

        bool destroy() const;

        kilograms getMass() const;

        std::string getName() const;

        ObjectType getType() const;

        void setPosition(Vector2D position);

        void setRotation(radians rotation);

        void setVelocity(Vector2D velocity);

        void setAngularVelocity(double radiansPerSecond);

        void setIsStatic(bool isStatic);

        void setToDestroy(bool destroy);

        void setMass(kilograms mass);

        void setName(std::string name);

        // inherited

        virtual void applySettings(ResourceDescriptor settings) override;

    private:

        Vector2D m_position;
        radians m_rotation;

        UniqueId m_uniqueId; ///< Object's uniqueId
        Vector2D m_velocity; ///< Object's velocity
        double m_angularVelocity; ///< Object's angular velocity about z-axis in radians per second
        bool m_isStatic; ///< If object is static, it does not move or intersect other static objects
        bool m_destroy; ///< if the object should be destroyed at the end of the frame
        kilograms m_mass; ///< mass in kilograms of the object
        std::string m_name; ///< label used for debugging
        ObjectType m_type; ///< Type of object

    }; // GameObject class
} // BattleRoom namespace
#endif // GAME_OBJECT_H

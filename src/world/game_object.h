#ifndef BATTLE_ROOM_GAME_OBJECT_H
#define BATTLE_ROOM_GAME_OBJECT_H

#include "display_window/drawable_object.h"
#include "common/vector2d.h"
#include "common/unique_id.h"
#include "world/command.h"
#include "world/object_type.h"

namespace BattleRoom {

    class GameObject : public DrawableObject {

    public:

        // constructor
        GameObject(UniqueId uniqueId, ObjectType type);

        ~GameObject() override = default;

        virtual void reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal);

        virtual void updateAnimation(seconds timestep);

        virtual void updateForNext(seconds timestep);

        virtual bool interpretCommand(const Command &cmd);

        virtual std::vector<GameObject *> getAddedObjects();

        virtual GameObject *clone() const;

        void setUp(Vector2D up);

        Projection1D projectOnto(Vector2D vec);

        // getters and setters

        const UniqueId getUniqueId() const;

        Vector2D getPosition();

        radians getRotation() const;

        Vector2D getVelocity();

        double getAngularVelocity() const;

        bool isStatic() const;

        bool isCollidable() const;

        bool destroy() const;

        kilograms getMass() const;

        std::string getName() const;

        ObjectType getType() const;

        void setPosition(Vector2D position);

        void setRotation(radians rotation);

        void setVelocity(Vector2D velocity);

        void setAngularVelocity(double radiansPerSecond);

        void setIsStatic(bool isStatic);

        void setIsCollidable(bool isCollidable);

        void setToDestroy(bool destroy);

        void setMass(kilograms mass);

        void setName(std::string name);

        // inherited

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        void serialize(BinaryStream &bs) const override;

        static GameObject deserialize(BinaryStream &bs);

    private:

        Vector2D m_position;
        radians m_rotation;

        UniqueId m_uniqueId; ///< Object's uniqueId
        Vector2D m_velocity; ///< Object's velocity
        double m_angularVelocity; ///< Object's angular velocity about z-axis in radians per second
        bool m_isStatic; ///< If object is static, it does not move or intersect other static objects
        bool m_isCollidable; ///< If object is collidable, it can intersect other objects
        bool m_destroy; ///< if the object should be destroyed at the end of the frame
        kilograms m_mass; ///< mass in kilograms of the object
        std::string m_name; ///< label used for debugging
        ObjectType m_type; ///< Type of object

        GameObject(const DrawableObject &base);

    }; // GameObject class

    /**
     * Unique pointer to camera instance
     */
    typedef std::unique_ptr<GameObject> UniqueGameObject;

} // BattleRoom namespace
#endif // BATTLE_ROOM_GAME_OBJECT_H

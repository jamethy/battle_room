#ifndef BATTLE_ROOM_BULLET_H
#define BATTLE_ROOM_BULLET_H

#include "world/game_object.h"

namespace BattleRoom {

    /**
     * Class for the object that is a great big red ball
     */
    class Bullet : public GameObject {

    public:

        // constructor
        explicit Bullet(UniqueId id);

        void setSource(UniqueId id);

        // inherited
        void reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal) override;

        void updateAnimation(seconds timestep) override;

        GameObject *clone() const override;

        void serialize(BinaryStream &bs) const override;

        static Bullet deserialize(BinaryStream &bs);

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        /**
         * State of ball object
         */
        enum class BulletState {
            Normal = 0,
            Hit
        };

    private:

        BulletState m_state; /// Current state of the ball object
        UniqueId m_bulletSource;
        seconds m_timeSinceFired;

        explicit Bullet(const GameObject &obj);

    }; // Bullet class
} // BattleRoom namespace
#endif //BATTLE_ROOM_BULLET_H

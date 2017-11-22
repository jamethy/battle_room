#ifndef BATTLE_ROOM_BULLET_H
#define BATTLE_ROOM_BULLET_H

#include "battle_room/game/game_object.h"

namespace BattleRoom {

    /**
     * Class for the object that is a great big red ball
     */
    class Bullet : public GameObject {

    public:

        // constructor
        Bullet(UniqueId id);

        // inherited
        void reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal) override;

        void updateAnimation(seconds timestep) override;

        GameObject* clone() const override;

        virtual void serialize(BinaryStream& bs) const override;
        static Bullet deserialize(BinaryStream& bs);

    private:

        /**
         * State of ball object
         */
        enum class BulletState {
            Normal = 0,
            Hit
        };

        BulletState m_state; /// Current state of the ball object

        Bullet(const GameObject& obj);

    }; // Bullet class
} // BattleRoom namespace
#endif //BATTLE_ROOM_BULLET_H

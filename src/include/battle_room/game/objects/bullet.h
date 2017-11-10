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

        GameObject* clone() override;

    private:

        /**
         * State of ball object
         */
        enum class BulletState {
            Normal,
            Hit
        };

        BulletState m_state; /// Current state of the ball object
    }; // Bullet class
} // BattleRoom namespace
#endif //BATTLE_ROOM_BULLET_H

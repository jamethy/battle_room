#ifndef PROJECT_DEATHBLADE_BULLET_H
#define PROJECT_DEATHBLADE_BULLET_H

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
        void reactToCollision(Vector3D velocityResult, Vector3D intersectionNormal) override;

        void updateAnimation(seconds timestep) override;

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
#endif //PROJECT_DEATHBLADE_BULLET_H

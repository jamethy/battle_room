#ifndef BALL_H
#define BALL_H

#include "battle_room/game/game_object.h"

namespace BattleRoom {

    /**
     * Class for the object that is a great big red ball
     */
    class Ball : public GameObject {

    public:

        // constructor
        Ball(UniqueId id);

        // inherited
        void reactToCollision(Vector3D velocityResult, Vector3D intersectionNormal) override;

        void updateAnimation(seconds timestep) override;

    private:

        /**
         * State of ball object
         */
        enum class BallState {
            Normal,
            Bouncing
        };

        Vector3D m_storedVelocity; /// Velocity resulting from a collision
        BallState m_state; /// Current state of the ball object

    }; // Ball class
} // BattleRoom namespace
#endif //BALL_H

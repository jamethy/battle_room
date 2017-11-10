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
        void reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal) override;

        void updateAnimation(seconds timestep) override;

        GameObject* clone() override;


    private:

        /**
         * State of ball object
         */
        enum class BallState {
            Normal,
            Bouncing
        };

        Vector2D m_storedVelocity; /// Velocity resulting from a collision
        BallState m_state; /// Current state of the ball object

    }; // Ball class
} // BattleRoom namespace
#endif //BALL_H

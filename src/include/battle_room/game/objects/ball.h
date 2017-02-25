#ifndef BALL_H
#define BALL_H

#include "battle_room/game/game_object.h"

namespace BattleRoom {

    class Ball : public GameObject {

    public:

        Ball(UniqueId id);

        void reactToCollision(Vector3D velocityResult, Vector3D intersectionNormal) override;
        void updateAnimation(seconds timestep) override;

    private:

        enum class BallState {
            Normal,
            Bouncing
        };

        Vector3D m_storedVelocity;
        BallState m_state;

    }; // Ball class
} // BattleRoom namespace
#endif //BALL_H

#ifndef BATTLE_ROOM_BALL_H
#define BATTLE_ROOM_BALL_H

#include "world/game_object.h"

namespace BattleRoom {

    /**
     * Class for the object that is a great big red ball
     */
    class Ball : public GameObject {

    public:

        // constructor
        explicit Ball(UniqueId id);

        // inherited
        void reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal) override;

        void updateAnimation(seconds timestep) override;

        GameObject *clone() const override;

        void serialize(BinaryStream &bs) const override;

        static Ball deserialize(BinaryStream &bs);

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        /**
         * State of ball object
         */
        enum BallState {
            Normal = 0,
            Bouncing
        };

    private:

        Vector2D m_storedVelocity; /// Velocity resulting from a collision
        BallState m_state; /// Current state of the ball object

        Ball(const GameObject &obj);

    }; // Ball class
} // BattleRoom namespace
#endif //BATTLE_ROOM_BALL_H

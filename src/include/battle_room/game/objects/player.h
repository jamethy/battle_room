#ifndef BATTLE_ROOM_PLAYER_H
#define BATTLE_ROOM_PLAYER_H

#include "battle_room/game/game_object.h"

namespace BattleRoom {

    /**
     * Class for the object that is a great big red ball
     */
    class Player : public GameObject {

    public:

        // constructor
        Player(UniqueId id);

        // inherited
        void reactToCollision(Vector3D velocityResult, Vector3D intersectionNormal) override;

        void updateAnimation(seconds timestep) override;

    private:

        /**
         * State of player object
         */
        enum class PlayerState {
            Flying,
            Landing,
            Landed
        };

        PlayerState m_state; /// Current state of the ball object

    }; // Player class
} // BattleRoom namespace
#endif //BATTLE_ROOM_PLAYER_H

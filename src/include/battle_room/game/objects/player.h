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

        void shootBullet(Vector2D aim);

        // inherited
        void reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal) override;

        void updateAnimation(seconds timestep) override;

        void updateForNext(seconds timestep) override;

        bool interpretCommand(Command& cmd) override;

        std::vector<GameObject*> getAddedObjects() override;

    private:

        /**
         * State of player object
         */
        enum class PlayerState {
            Flying,
            Landing,
            Landed
        };

        PlayerState m_state; /// Current state of the player object
        Vector2D m_aim; // point aiming att
        std::vector<GameObject*> m_addedObjects;

    }; // Player class
} // BattleRoom namespace
#endif //BATTLE_ROOM_PLAYER_H

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

        void jump(Vector2D aim);

        // inherited
        void reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal) override;

        void updateAnimation(seconds timestep) override;

        void updateForNext(seconds timestep) override;

        bool interpretCommand(Command& cmd) override;

        std::vector<GameObject*> getAddedObjects() override;

        static ObjectType type();

    private:

        /**
         * State of player object
         */
        enum class PlayerState {
            Flying,
            Landing,
            Landed,
            Frozen
        };

        PlayerState m_state; /// Current state of the player object
        Vector2D m_aim; // point aiming att
        std::vector<GameObject*> m_addedObjects;

        bool m_chargingGun = false;
        double m_gunCharge = 0;

        bool m_chargingJump = false;
        double m_jumpCharge = 0;

    }; // Player class
} // BattleRoom namespace
#endif //BATTLE_ROOM_PLAYER_H

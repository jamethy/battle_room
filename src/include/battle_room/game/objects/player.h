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

        bool isChargingGun() const;
        bool isChargingJump() const;
        double getGunCharge() const;
        double getJumCharge() const;

        // inherited
        void reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal) override;

        void updateAnimation(seconds timestep) override;

        void updateForNext(seconds timestep) override;

        bool interpretCommand(const Command& cmd) override;

        std::vector<GameObject*> getAddedObjects() override;

        GameObject* clone() const override;

        UniqueId getClient() const;

        static ObjectType type();

        virtual void applySettings(ResourceDescriptor settings) override;
        virtual void serialize(BinaryStream& bs) const override;
        static Player deserialize(BinaryStream& bs);

    private:

        UniqueId m_client;

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

        bool m_chargingGun;
        double m_gunCharge;

        bool m_chargingJump;
        double m_jumpCharge;

        Player(const GameObject& obj);

    }; // Player class
} // BattleRoom namespace
#endif //BATTLE_ROOM_PLAYER_H

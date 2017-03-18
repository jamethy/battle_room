#include <src/include/battle_room/common/animation_handler.h>
#include "battle_room/game/objects/player.h"

#include <iostream>

namespace BattleRoom {

    // constructors
    Player::Player(UniqueId id)
            : GameObject(id, ObjectType::Player),
              m_state(PlayerState::Flying) {}

    // other functions
    void Player::reactToCollision(Vector3D velocityResult, Vector3D intersectionNormal) {

        m_state = PlayerState::Landing;

        setIsStatic(true);

        setAnimation(AnimationHandler::getAnimation("player_landing"));
        setAnimationState(0.0);

        // lasts .44 seconds
        Vector3D v = getVelocity().getUnit();
        double m = v.dot(intersectionNormal);
        std::cout << "m : " << m << std::endl;

        setVelocity(v.times(1.6/ (m * (m < 0 ? -1 : 1))));

        radians angleDelta = getOrientation().getAngleFrom(intersectionNormal.times(-1));
        setAngularVelocity(angleDelta/0.44);
    }

    void Player::updateAnimation(seconds timestep) {

        if (m_state == PlayerState::Landed) {
            return;
        }

        if (m_state == PlayerState::Flying) {
            GameObject::updateAnimation(timestep);
        }
        else if (m_state == PlayerState::Landing) {
            Animation &animation = getAnimation();
            seconds newState = getAnimationState() + timestep;

            if (newState > animation.getLength()) {

                // set the new state (time elapsed since end of last animation)
                setAnimationState(newState - animation.getLength());

                // find the new animation
                setAnimation(AnimationHandler::getAnimation(animation.getNextAnimation()));
                m_state = PlayerState::Landed;
                setVelocity(Vector3D(0,0,0));
                setAngularVelocity(0);
            } else {

                // iterate object->animation
                setAnimationState(newState);
            }
        }
    }

} // BattleRoom namespace


#include <src/include/battle_room/common/animation_handler.h>
#include "battle_room/game/objects/ball.h"

namespace BattleRoom {

// constructors
    Ball::Ball(UniqueId id)
            : GameObject(id, ObjectType::Ball),
              m_state(BallState::Normal) {}

    // other functions
    void Ball::reactToCollision(Vector3D velocityResult, Vector3D intersectionNormal) {

        m_state = BallState::Bouncing;
        m_storedVelocity = velocityResult;

        Vector3D temp = intersectionNormal.cross(Vector3D(0, 0, 1));
        setVelocity(temp.times(velocityResult.dot(temp)));
        setIsStatic(true);

        Vector3D h = intersectionNormal.plus(Vector3D(0, 1, 0)).getUnit();
        setOrientation(Quaternion(h.y(), 0, 0, -h.x()));

        setAnimation(AnimationHandler::getAnimation("ball_bounce"));
        setAnimationState(0.0);
    }

    void Ball::updateAnimation(seconds timestep) {

        if (m_state == BallState::Normal) {
            return;
        }

        if (m_state == BallState::Bouncing) {
            Animation &animation = getAnimation();
            seconds newState = getAnimationState() + timestep;

            if (newState > animation.getLength()) {

                // set the new state (time elapsed since end of last animation)
                setAnimationState(newState - animation.getLength());

                // find the new animation
                setAnimation(AnimationHandler::getAnimation(animation.getNextAnimation()));
                m_state = BallState::Normal;
                setVelocity(m_storedVelocity);
                setIsStatic(false);
            } else {

                // iterate object->animation
                setAnimationState(newState);
            }

        }
    }

} // BattleRoom namespace



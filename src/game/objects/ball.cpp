#include "battle_room/game/objects/ball.h"
#include "battle_room/common/animation_handler.h"

namespace BattleRoom {

// constructors
    Ball::Ball(UniqueId id)
            : GameObject(id, ObjectType::Ball),
              m_state(BallState::Normal) {}

    // other functions
    void Ball::reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal) {

        m_state = BallState::Bouncing;
        m_storedVelocity = velocityResult; // ball will bounce after

        // have the ball slide along the other object by setting it velocity to normal the normal
        Vector2D temp = Vector2D(-intersectionNormal.y(), intersectionNormal.x());
        setVelocity(temp.times(velocityResult.dot(temp)));
        setIsStatic(true);

        setUp(intersectionNormal);

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



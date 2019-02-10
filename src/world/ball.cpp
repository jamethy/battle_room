#include "world/ball.h"
#include "animation/animation_handler.h"

namespace BattleRoom {

// constructors
    Ball::Ball(UniqueId id)
            : GameObject(id, ObjectType::Ball),
              m_state(BallState::Normal) {}

    Ball::Ball(const GameObject& obj) :
        GameObject(obj),
        m_state(BallState::Normal) 
    {}

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

    GameObject* Ball::clone() const {
        return new Ball(*this);
    }

    void Ball::serialize(BinaryStream& bs) const {
        GameObject::serialize(bs);
        m_storedVelocity.serialize(bs);
        bs.writeInt((int)m_state);
    }

    Ball Ball::deserialize(BinaryStream& bs) {
        Ball ball(GameObject::deserialize(bs));
        ball.m_storedVelocity = Vector2D::deserialize(bs);
        ball.m_state = (BallState)bs.readInt();
        return ball;
    }

    std::string ballStateString(Ball::BallState state) {
        switch (state) {
            case Ball::BallState::Bouncing:
                return "Bouncing";
            case Ball::BallState::Normal:
            default:
                return "Normal";
        }
    }

    Ball::BallState stringBallState(const std::string &str) {
        if (str == "Bouncing") {
            return Ball::BallState::Bouncing;
        } else {
            return Ball::BallState::Normal;
        }
    }

    void Ball::applySettings(ResourceDescriptor settings) {
        GameObject::applySettings(settings);

        m_state = stringBallState(settings.getSubResource("State").getValue());
        m_storedVelocity.applySettings(settings.getSubResource("StoredVelocity"));
    }

    ResourceDescriptor Ball::getSettings() const {
        auto rd = GameObject::getSettings();
        auto subs = rd.getSubResources();

        rd.setKey("Ball");
        subs.emplace_back("State", ballStateString(m_state));

        auto subRd = m_storedVelocity.getSettings();
        subRd.setKey("StoreVelocity");
        subs.push_back(subRd);

        rd.setSubResources(subs);
        return rd;
    }

} // BattleRoom namespace



#include <src/include/battle_room/common/animation_handler.h>
#include "battle_room/game/objects/player.h"
#include "battle_room/game/objects/bullet.h"

#include <cmath>

const double MAX_ANGULAR_VEL = 1; // radians per second
const double BULLET_SPEED = 30; // meters per second

namespace BattleRoom {

    // constructors
    Player::Player(UniqueId id)
            : GameObject(id, ObjectType::Player),
            m_state(PlayerState::Flying) {
                setAnimation(AnimationHandler::getAnimation("man_0"));
            }

    // other functions
    void Player::reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal) {
        (void)velocityResult; // unused

        m_state = PlayerState::Landing;

        setIsStatic(true);

        setAnimation(AnimationHandler::getAnimation("player_landing"));
        setAnimationState(0.0);

        // lasts .44 seconds
        Vector2D v = getVelocity().getUnit();
        double m = v.dot(intersectionNormal);

        setVelocity(v.times(1.6/ (m * (m < 0 ? -1 : 1))));
    }

    void Player::updateAnimation(seconds timestep) {

        if (m_state == PlayerState::Landed) {
            return;
        }

        if (m_state == PlayerState::Flying) {

            Vector2D delta = m_aim.minus(getPosition());
            radians exactAngle = (PI*0.5 + getRotation()) - std::atan2(delta.y(), delta.x());
            degrees aimAngle = under180(45*round(toDegrees(exactAngle)/45));

            std::string animationName = "man_";
            if (aimAngle < 0) {
                animationName += "n" + std::to_string((int)std::abs(aimAngle));
            } else {
                animationName += std::to_string((int)std::abs(aimAngle));
            }

            setAnimation(AnimationHandler::getAnimation(animationName));
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
                setVelocity(Vector2D(0, 0));
                setAngularVelocity(0);
            } else {

                // iterate object->animation
                setAnimationState(newState);
            }
        }
    }

    radians diffOfAngles(radians a, radians b) {
        return fmod(a - b + PI, 2*PI) - PI;

    }

    double calcFlyingAngularVelocity(Vector2D vel, radians angle, double current) {

        if (current > MAX_ANGULAR_VEL) {
            return 0.9*current;
        } else {
            radians desired = std::atan2(vel.x(), -vel.y());
            radians diff = diffOfAngles(desired, angle);

            if (diff*current < 0) {
                diff = diff + (current > 0 ? 2*PI : -2*PI);
            }
            return diff;
        }
    }

    void Player::updateForNext(seconds timestep) {
        (void)timestep; // unused

        if (m_state == PlayerState::Flying) {
            // desired is feet leading
            setAngularVelocity(calcFlyingAngularVelocity(getVelocity(), getRotation(), getAngularVelocity()));
        }
    }

    void Player::shootBullet(Vector2D aim) {
        m_aim = aim;
        Bullet *bullet = new Bullet(UniqueId::generateNewNetworkId());
        Vector2D bulletVelUnit = m_aim.minus(getPosition()).getUnit();

        const Frame& frame = getAnimation().getFrame(getAnimationState());
        meters dist = std::max(frame.getWidth(), frame.getHeight()) / 2;

        bullet->setVelocity(bulletVelUnit.times(BULLET_SPEED).plus(getVelocity()));
        bullet->setRotation(bulletVelUnit.angle());
        bullet->setPosition(getPosition().plus(bulletVelUnit.times(dist)));

        m_addedObjects.push_back(bullet);
    }

    bool Player::interpretCommand(Command& cmd) {
        if (GameObject::interpretCommand(cmd)) {
            if (CommandType::Aim == cmd.getType()) {
                m_aim = cmd.getPoint();
            } else if (CommandType::Shoot == cmd.getType()) {
                shootBullet(cmd.getPoint());
            }
            return true;
        }
        return false;
    }

    std::vector<GameObject*> Player::getAddedObjects() {
        std::vector<GameObject*> objects = m_addedObjects;
        m_addedObjects.clear();
        return objects;
    }

} // BattleRoom namespace


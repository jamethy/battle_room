#include <src/include/battle_room/common/animation_handler.h>
#include "battle_room/game/objects/player.h"
#include "battle_room/game/objects/bullet.h"

#include <cmath>
#include <iostream>

const double MAX_ANGULAR_VEL = 1; // radians per second
const double MAX_BULLET_SPEED = 60; // meters per second
const double MIN_BULLET_SPEED = 20; // meters per second
const double MAX_JUMP_SPEED = 6; // meters per second
const double MIN_JUMP_SPEED = 2; // meters per second

namespace BattleRoom {

    // constructors
    Player::Player(UniqueId id)
            : GameObject(id, ObjectType::Player),
            m_state(PlayerState::Flying) {
                setAnimation(AnimationHandler::getAnimation("man_0"));
            }

    // other functions
    void Player::reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal) {

        velocityResult = velocityResult.times(0.7);

        if (m_state == PlayerState::Frozen) {
            if (velocityResult.magnitude() < 0.01) {
                setVelocity(Vector2D(0, 0));
            } else {
                setVelocity(velocityResult);
            }

        } else {
            m_state = PlayerState::Landed;

            // move to wall after rotating
            const Frame& frame = getAnimation().getFrame(getAnimationState());
            Projection1D rotated = frame.getBoundarySet().projectOnto(intersectionNormal.getRotated(-getRotation()));
            Projection1D upright = frame.getBoundarySet().projectOnto(Vector2D(0, 1));
            meters delta = rotated.getMin() - upright.getMin();
            setPosition(getPosition().plus(intersectionNormal.times(delta)));

            setIsStatic(true);
            setVelocity(Vector2D(0, 0));
            setAngularVelocity(0);

            setUp(intersectionNormal);
        }
    }

    void Player::updateAnimation(seconds timestep) {

        if (m_state != PlayerState::Frozen) {
            // should be dependent on m_state, m_chargingGun, m_chargingJump

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

        if (m_state == PlayerState::Flying) {
            // desired is feet leading
            setAngularVelocity(calcFlyingAngularVelocity(getVelocity(), getRotation(), getAngularVelocity()));
        }

        m_gunCharge = m_chargingGun ? std::min(m_gunCharge + timestep, 1.0) : 0;
        m_jumpCharge = m_chargingJump ? std::min(m_jumpCharge + timestep, 1.0) : 0;
    }

    void Player::shootBullet(Vector2D aim) {
        m_aim = aim;
        Bullet *bullet = new Bullet(UniqueId::generateNewNetworkId());
        Vector2D bulletVelUnit = m_aim.minus(getPosition()).getUnit();

        const Frame& frame = getAnimation().getFrame(getAnimationState());
        meters dist = std::max(frame.getWidth(), frame.getHeight()) / 2;

        double speed = std::max(m_gunCharge*MAX_BULLET_SPEED, MIN_BULLET_SPEED);
        bullet->setVelocity(bulletVelUnit.times(speed).plus(getVelocity()));
        bullet->setRotation(bulletVelUnit.angle());
        bullet->setPosition(getPosition().plus(bulletVelUnit.times(dist)));

        m_gunCharge = 0;
        m_chargingGun = false;

        m_addedObjects.push_back(bullet);
    }

    void Player::jump(Vector2D aim) {
        if (m_state == PlayerState::Landed) {

            setIsStatic(false);
            m_state = PlayerState::Flying;
            double speed = std::max(m_jumpCharge*MAX_JUMP_SPEED, MIN_JUMP_SPEED);
            setVelocity(aim.minus(getPosition()).getUnit().times(speed));

            m_jumpCharge = 0;
            m_chargingJump = false;
        }
    }

    bool Player::interpretCommand(Command& cmd) {
        if (GameObject::interpretCommand(cmd)) {

            if (m_state == PlayerState::Frozen) {
                return true;
            }

            switch (cmd.getType()) {
                case CommandType::Aim:
                    m_aim = cmd.getPoint();
                    break;
                case CommandType::ShootCharge:
                    m_chargingGun = true;
                    break;
                case CommandType::ShootRelease:
                    shootBullet(cmd.getPoint());
                    break;
                case CommandType::JumpCharge:
                    m_chargingJump = true;
                    break;
                case CommandType::JumpRelease:
                    jump(cmd.getPoint());
                    break;
                case CommandType::Freeze:
                    m_state = PlayerState::Frozen;
                    break;
                default:
                    break;

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


#include "animation_handler.h"
#include "bullet.h"

namespace BattleRoom {

    // constructors
    Bullet::Bullet(UniqueId id) : 
        GameObject(id, ObjectType::Bullet),
        m_state(BulletState::Normal) {
            setAnimation(AnimationHandler::getAnimation("bullet"));
        }

    Bullet::Bullet(const GameObject& obj) :
        GameObject(obj),
        m_state(BulletState::Normal)
    { }

    // other functions
    void Bullet::reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal) {
        (void)velocityResult; // unused
        (void)intersectionNormal; // unused

        m_state = BulletState::Hit;

        setVelocity(getVelocity().times(0.1));

        setAnimation(AnimationHandler::getAnimation("bullet_hit"));
        setAnimationState(0.0);
        setIsStatic(true); // bullet hit has no hit box
    }

    void Bullet::updateAnimation(seconds timestep) {

        if (m_state == BulletState::Normal) {
            GameObject::updateAnimation(timestep);
            return;
        }

        if (m_state == BulletState::Hit) {
            Animation &animation = getAnimation();
            seconds newState = getAnimationState() + timestep;

            if (newState > animation.getLength()) {
                setToDestroy(true);
            }
            else {
                GameObject::updateAnimation(timestep);
            }
            return;
        }
    }

    GameObject* Bullet::clone() const {
        return new Bullet(*this);
    }

    void Bullet::serialize(BinaryStream& bs) const {
        GameObject::serialize(bs);
        bs.writeInt((int)m_state);
    }

    Bullet Bullet::deserialize(BinaryStream& bs) {
        Bullet bullet(GameObject::deserialize(bs));
        bullet.m_state = (BulletState)bs.readInt();
        return bullet;
    }

} // BattleRoom namespace
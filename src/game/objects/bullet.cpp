
#include <src/include/battle_room/common/animation_handler.h>
#include "battle_room/game/objects/bullet.h"

namespace BattleRoom {

    // constructors
    Bullet::Bullet(UniqueId id) : 
        GameObject(id, ObjectType::Bullet),
        m_state(BulletState::Normal) {
            setAnimation(AnimationHandler::getAnimation("bullet"));
        }

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

} // BattleRoom namespace

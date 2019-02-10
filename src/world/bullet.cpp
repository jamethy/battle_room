
#include "animation/animation_handler.h"
#include "world/bullet.h"

namespace BattleRoom {

    // constructors
    Bullet::Bullet(UniqueId id) :
            GameObject(id, ObjectType::Bullet),
            m_state(BulletState::Normal),
            m_bulletSource(UniqueId::generateInvalidId()),
            m_timeSinceFired(0) {
        setAnimation(AnimationHandler::getAnimation("bullet"));
        setIsCollidable(false);
    }

    Bullet::Bullet(const GameObject &obj) :
            GameObject(obj),
            m_state(BulletState::Normal),
            m_bulletSource(UniqueId::generateInvalidId()),
            m_timeSinceFired(0) {
        setIsCollidable(false);
    }

    // other functions
    void Bullet::reactToCollision(Vector2D velocityResult, Vector2D intersectionNormal) {
        (void) velocityResult; // unused
        (void) intersectionNormal; // unused

        m_state = BulletState::Hit;

        setVelocity(getVelocity().times(0.1));

        setAnimation(AnimationHandler::getAnimation("bullet_hit"));
        setAnimationState(0.0);
        setIsStatic(true); // bullet hit has no hit box
    }

    void Bullet::updateAnimation(seconds timestep) {

        m_timeSinceFired += timestep;
        if (m_timeSinceFired > 0.01) {
            setIsCollidable(true);
        }

        if (m_state == BulletState::Normal) {
            GameObject::updateAnimation(timestep);
            return;
        }

        if (m_state == BulletState::Hit) {
            Animation &animation = getAnimation();
            seconds newState = getAnimationState() + timestep;

            if (newState > animation.getLength()) {
                setToDestroy(true);
            } else {
                GameObject::updateAnimation(timestep);
            }
            return;
        }
    }

    GameObject *Bullet::clone() const {
        return new Bullet(*this);
    }

    void Bullet::serialize(BinaryStream &bs) const {
        GameObject::serialize(bs);
        bs.writeInt((int) m_state);
        m_bulletSource.serialize(bs);
        bs.writeSeconds(m_timeSinceFired);
    }

    Bullet Bullet::deserialize(BinaryStream &bs) {
        Bullet bullet(GameObject::deserialize(bs));
        bullet.m_state = (BulletState) bs.readInt();
        bullet.m_bulletSource = UniqueId::deserialize(bs);
        bullet.m_timeSinceFired = bs.readSeconds();
        return bullet;
    }

    void Bullet::setSource(UniqueId id) {
        m_bulletSource = id;
    }

    std::string bulletStateString(Bullet::BulletState state) {
        switch (state) {
            case Bullet::BulletState::Hit:
                return "Hit";
            case Bullet::BulletState::Normal:
            default:
                return "Normal";
        }
    }

    Bullet::BulletState stringBulletState(const std::string &str) {
        if (str == "Hit") {
            return Bullet::BulletState::Hit;
        } else {
            return Bullet::BulletState::Normal;
        }
    }

    void Bullet::applySettings(ResourceDescriptor settings) {
        GameObject::applySettings(settings);

        m_state = stringBulletState(settings.getSubResource("State").getValue());
        m_bulletSource = UniqueId::fromString(settings.getSubResource("Source").getValue());
        auto sub = settings.getSubResource("TimeSinceFired").getValue();
        if (isNotEmpty(sub)) {
            m_timeSinceFired = toSeconds(sub);
        }
    }

    ResourceDescriptor Bullet::getSettings() const {
        auto rd = GameObject::getSettings();
        rd.emplaceSubResource("Type", "Bullet");
        rd.emplaceSubResource("State", bulletStateString(m_state));
        rd.emplaceSubResource("Source", m_bulletSource.toString());
        rd.emplaceSubResource("TimeSinceFired", m_bulletSource.toString());
        return rd;
    }
} // BattleRoom namespace

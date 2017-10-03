#include "object_intersection.h"
#include <cmath>
#include <algorithm>

const double ELASTICITY = 0.95;

namespace BattleRoom {

    Command FREEZE = Command(CommandType::Freeze, UniqueId::generateInvalidId(), Vector2D(0, 0));

    // constructor

    ObjectIntersection::ObjectIntersection(GameObject *objA, GameObject *objB, SatIntersection sat)
            : m_objectA(objA), m_objectB(objB),
              m_minTransMag(sat.getMinTranslationMagnitude()) {

        // back to world coordinates
        m_minTransUnit = sat.getMinTranslationUnitVector().getRotated(objA->getRotation());
    }

    void bounceOffStaticObject(GameObject *object, Vector2D minTransUnit, meters minTransMag) {

        Vector2D minTransVector = minTransUnit.times(minTransMag);

        meters speedNormal = object->getVelocity().dot(minTransUnit);

        Vector2D velocity = object->getVelocity().minus(minTransUnit.times((1 + ELASTICITY) * speedNormal));
        object->reactToCollision(velocity, minTransUnit);
    }

    void bounceOffDynamicObject(GameObject *objectA, GameObject *objectB, Vector2D minTransUnit, meters minTransMag) {

        Vector2D minTransVector = minTransUnit.times(minTransMag);

        double elasticity = 0.95;
        meters speedNormal = minTransUnit.dot(objectA->getVelocity().minus(objectB->getVelocity()));

        double aRatio = 0.5;
        double bRatio = 0.5;

        if (objectA->getMass() > 0 && objectB->getMass() > 0) {
            aRatio = (objectB->getMass() / (objectA->getMass() + objectB->getMass()));
            bRatio = (objectA->getMass() / (objectA->getMass() + objectB->getMass()));
        }

        Vector2D velocityA = objectA->getVelocity().minus(minTransUnit.times(aRatio * (1 + elasticity) * speedNormal));
        Vector2D velocityB = objectB->getVelocity().plus(minTransUnit.times(bRatio * (1 + elasticity) * speedNormal));

        objectA->reactToCollision(
                objectA->getVelocity().minus(minTransUnit.times(aRatio * (1 + elasticity) * speedNormal)),
                minTransUnit.times(-1));
        objectB->reactToCollision(
                objectB->getVelocity().plus(minTransUnit.times(bRatio * (1 + elasticity) * speedNormal)), minTransUnit);

    }

    void bulletReact(GameObject *bullet, GameObject *other, Vector2D minTransUnit, meters minTransMag) {
        (void) minTransMag; // unused

        switch (other->getType()) {

            case ObjectType::None:
            case ObjectType::Ball:
            case ObjectType::Wall:
                bullet->reactToCollision(Vector2D(0, 0), minTransUnit.times(-1));
                break;
            case ObjectType::Bullet:
                bullet->reactToCollision(Vector2D(0, 0), minTransUnit.times(-1));
                other->reactToCollision(Vector2D(0, 0), minTransUnit);
                break;
            case ObjectType::Player:
                bullet->reactToCollision(Vector2D(0, 0), minTransUnit.times(-1));
                other->interpretCommand(FREEZE);
                break;
        }

    }

    void ballReact(GameObject *ball, GameObject *other, Vector2D minTransUnit, meters minTransMag) {

        switch (other->getType()) {

            case ObjectType::None:
                break;
            case ObjectType::Ball:
                bounceOffDynamicObject(ball, other, minTransUnit, minTransMag);
                break;
            case ObjectType::Wall:
                bounceOffStaticObject(ball, minTransUnit, minTransMag);
                break;
            case ObjectType::Bullet:
                other->reactToCollision(Vector2D(0, 0), minTransUnit);
                break;
            case ObjectType::Player:
                break;
        }

    }

    void playerReact(GameObject *player, GameObject *other, Vector2D minTransUnit, meters minTransMag) {
        (void)minTransMag; // unused

        switch (other->getType()) {

            case ObjectType::None:
                bounceOffStaticObject(player, minTransUnit, minTransMag);
                break;
            case ObjectType::Ball:
                break;
            case ObjectType::Wall:
                bounceOffStaticObject(player, minTransUnit, minTransMag);
                break;
            case ObjectType::Bullet:
                other->reactToCollision(Vector2D(0, 0), minTransUnit.times(-1));
                player->interpretCommand(FREEZE);
                break;
            case ObjectType::Player:
                break;
        }

    }

    void wallReact(GameObject *wall, GameObject *other, Vector2D minTransUnit, meters minTransMag) {
        (void)wall; // unused

        switch (other->getType()) {
            case ObjectType::Ball:
                bounceOffStaticObject(other, minTransUnit.times(-1), minTransMag);
                break;
            case ObjectType::Wall:
            case ObjectType::None:
            case ObjectType::Bullet:
                other->reactToCollision(Vector2D(0, 0), minTransUnit);
                break;
            case ObjectType::Player:
                bounceOffStaticObject(other, minTransUnit, minTransMag);
                break;
        }

    }

    void noneReact(GameObject *object, GameObject *other, Vector2D minTransUnit, meters minTransMag) {

        if (object->isStatic()) {
            switch (other->getType()) {
                case ObjectType::Ball:
                    bounceOffStaticObject(other, minTransUnit, minTransMag);
                    break;
                case ObjectType::None:
                    if (!other->isStatic()) {
                        bounceOffStaticObject(other, minTransUnit, minTransMag);
                    }
                case ObjectType::Wall:
                case ObjectType::Bullet:
                case ObjectType::Player:
                    bounceOffStaticObject(other, minTransUnit, minTransMag);
                    break;
            }
        } else {
            switch (other->getType()) {
                case ObjectType::Ball:
                    bounceOffDynamicObject(object, other, minTransUnit, minTransMag);
                    break;
                case ObjectType::Wall:
                    bounceOffStaticObject(object, minTransUnit.times(-1), minTransMag);
                    break;
                case ObjectType::None:
                    if (other->isStatic()) {
                        bounceOffStaticObject(object, minTransUnit.times(-1), minTransMag);
                    } else {
                        bounceOffDynamicObject(object, other, minTransUnit, minTransMag);
                    }
                    break;
                case ObjectType::Bullet:
                case ObjectType::Player:
                    bounceOffStaticObject(other, minTransUnit, minTransMag);
                    break;
            }
        }
    }


    void ObjectIntersection::reactToCollision() {

        m_objectB->setPosition(m_objectB->getPosition().plus(m_minTransUnit.times(m_minTransMag)));

        switch (m_objectA->getType()) {
            case ObjectType::Ball:
                ballReact(m_objectA, m_objectB, m_minTransUnit, m_minTransMag);
                break;
            case ObjectType::Wall:
                wallReact(m_objectA, m_objectB, m_minTransUnit, m_minTransMag);
                break;
            case ObjectType::Bullet:
                bulletReact(m_objectA, m_objectB, m_minTransUnit, m_minTransMag);
                break;
            case ObjectType::Player:
                playerReact(m_objectA, m_objectB, m_minTransUnit, m_minTransMag);
                break;
            case ObjectType::None:
                noneReact(m_objectA, m_objectB, m_minTransUnit, m_minTransMag);
                break;
        }
    }

    SatIntersection checkForIntersection(GameObject *objectA, GameObject *objectB) {

        const BoundarySet &boundarySetA = objectA->getAnimation().getFrame(
                objectA->getAnimationState()).getBoundarySet();
        const BoundarySet &boundarySetB = objectB->getAnimation().getFrame(
                objectB->getAnimationState()).getBoundarySet();

        Vector2D delta = objectB->getPosition().minus(objectA->getPosition()).getRotated(-objectA->getRotation());
        radians angle = objectB->getRotation() - objectA->getRotation();

        SatIntersection intersection;
        intersection.setIntersects(false);

        for (Boundary *boundaryA : boundarySetA) {
            for (Boundary *boundaryB : boundarySetB) {

                intersection = boundaryA->intersects(boundaryB, delta, angle);

                if (intersection.doesIntersect()) {
                    return intersection;
                }
            }
        }
        return intersection;
    }

    std::vector<ObjectIntersection> ObjectIntersection::getIntersections(std::vector<GameObject *> objects) {

        std::vector<ObjectIntersection> intersections;

        for (size_t i = 0; i < objects.size(); ++i) {

            for (size_t j = i + 1; j < objects.size(); ++j) {
                GameObject *objectA = objects.at(i);
                GameObject *objectB = objects.at(j);

                if (objectA->isStatic() && objectB->isStatic()) {
                    continue;
                } else if (objectB->isStatic()) {
                    std::swap(objectA, objectB);
                }

                SatIntersection intersection = checkForIntersection(objectA, objectB);
                if (intersection.doesIntersect()) {
                    intersections.push_back(ObjectIntersection(objectA, objectB, intersection));
                }
            }
        }
        return intersections;
    }


    // getters

    GameObject *ObjectIntersection::getObjectA() {
        return m_objectA;
    }

    GameObject *ObjectIntersection::getObjectB() {
        return m_objectB;
    }

} // BattleRoom namespace

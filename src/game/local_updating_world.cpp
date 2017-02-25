#include "battle_room/game/local_updating_world.h"

#include "battle_room/common/animation_handler.h"
#include "battle_room/game/command_receiver.h"

#include <iostream>
#include <map>

// temp for fake load
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <cmath>

using std::vector;
using std::pair;

namespace BattleRoom {

typedef struct ObjectIntersection {

    ObjectIntersection(GameObject* objA, GameObject* objB, SatIntersection sat)
        : a(objA), b(objB),
          minTranslationUnit(sat.getMinTranslationUnitVector()),
          minTranslationMagnetidue(sat.getMinTranslationMagnitude())
    {}


    GameObject* a;
    GameObject* b;
    Vector2D minTranslationUnit;
    meters minTranslationMagnetidue;

} ObjectIntersection;

// apply settings

void LocalUpdatingWorld::applySettings(ResourceDescriptor settings) {

    World::applySettings(settings);

    ResourceDescriptor sub = settings.getSubResource("Time");
    if (isNotEmpty(sub.getValue())) {
        m_timeController.set(toSeconds(sub.getValue()));
        m_gameTime = m_timeController.get();
    }
}

// constructors
LocalUpdatingWorld::LocalUpdatingWorld() {
}

LocalUpdatingWorld::LocalUpdatingWorld(ResourceDescriptor settings) 
    : LocalUpdatingWorld()
{
    applySettings(settings);
}

void updateObjectAnimation(GameObject* object, seconds timestep) {

    Animation& animation = object->getAnimation();
    seconds newState = object->getAnimationState() + timestep;

    if (newState > animation.getLength()) {

        // set the new state (time elapsed since end of last animation)
        object->setAnimationState(newState - animation.getLength());

        // find the new animation
        animation = AnimationHandler::getAnimation(animation.getNextAnimation());
    }
    else {

        // iterate object->animation
        object->setAnimationState(newState);
    }

}

void moveObject(GameObject* object, seconds timestep) {
    object->setLocation(
            object->getLocation()
            .plus(object->getVelocity().times(timestep)
    ));
}

// other functions

SatIntersection checkForIntersection(GameObject* objectA, GameObject* objectB) {

    const BoundarySet& boundarySetA = objectA->getAnimation().getFrame(objectA->getAnimationState()).getBoundarySet();
    const BoundarySet& boundarySetB = objectB->getAnimation().getFrame(objectB->getAnimationState()).getBoundarySet();

    Vector3D delta = objectA->getOrientation().getInverseRotated(objectB->getLocation().minus(objectA->getLocation()));
    Vector2D dist(delta.x(),delta.y());

    // TODO write something to get angle from quaternion
    Vector3D x(1,0,0);
    x = objectA->getOrientation().getInverseRotated(objectB->getOrientation().getRotated(x));
    radians angle = std::atan2(x.y(),x.x());

    SatIntersection intersection;
    intersection.setIntersects(false);

    for (Boundary* boundaryA : boundarySetA) {
        for (Boundary* boundaryB : boundarySetB) {

            intersection = boundaryA->intersects(boundaryB, dist, angle);

            if (intersection.doesIntersect()) {
                return intersection;
            }
        }
    }
    return intersection;
}

void bounceOffStaticObject(GameObject* object, Vector3D minTransUnit, meters minTransMag) {

    Vector3D minTransVector = minTransUnit.times(minTransMag);

    double elasticity = 0.95;

    meters speedNormal = object->getVelocity().dot(minTransUnit);

    Vector3D velocity = object->getVelocity().minus( minTransUnit.times((1 + elasticity) * speedNormal));
    object->setLocation(object->getLocation().plus(minTransVector));
    object->setVelocity(velocity);
}

void bounceOffDynamicObject(GameObject* objectA, GameObject* objectB, Vector3D minTransUnit, meters minTransMag) {

    Vector3D minTransVector = minTransUnit.times(minTransMag);

    double elasticity = 0.95;
    meters speedNormal = minTransUnit.dot(objectA->getVelocity().minus(objectB->getVelocity()));

    double aRatio = 0.5;
    double bRatio = 0.5;

    if (objectA->getMass() > 0 && objectB->getMass() > 0) {
        aRatio = (objectB->getMass() / (objectA->getMass() + objectB->getMass()));
        bRatio = (objectA->getMass() / (objectA->getMass() + objectB->getMass()));
    }

    Vector3D velocityA = objectA->getVelocity().minus(minTransUnit.times(aRatio * (1 + elasticity) * speedNormal));
    Vector3D velocityB = objectB->getVelocity().plus(minTransUnit.times(bRatio * (1 + elasticity) * speedNormal));

    // check if energy is conserved
    objectA->setLocation(objectA->getLocation().minus(minTransVector.times(-aRatio / 2.0)));
    objectB->setLocation(objectB->getLocation().plus(minTransVector.times(bRatio / 2.0)));

    objectA->setVelocity(objectA->getVelocity().minus(minTransUnit.times(aRatio * (1 + elasticity) * speedNormal)));
    objectB->setVelocity(objectB->getVelocity().plus(minTransUnit.times(bRatio * (1 + elasticity) * speedNormal)));

}

void ballReact(GameObject* ball, GameObject* other, Vector3D minTransUnit, meters minTransMag) {

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
        case ObjectType::Player:
            break;
    }

}

void wallReact(GameObject* wall, GameObject* other, Vector3D minTransUnit, meters minTransMag) {

    switch (other->getType()) {
        case ObjectType::Ball:
            bounceOffStaticObject(other, minTransUnit, minTransMag);
            break;
        case ObjectType::Wall:
        case ObjectType::None:
        case ObjectType::Bullet:
        case ObjectType::Player:
            break;
    }

}

void noneReact(GameObject* object, GameObject* other, Vector3D minTransUnit, meters minTransMag) {

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
                break;
        }
    }
    else {
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
                }
                else {
                    bounceOffDynamicObject(object, other, minTransUnit, minTransMag);
                }
                break;
            case ObjectType::Bullet:
            case ObjectType::Player:
                break;
        }
    }
}


void react(GameObject* objectA, GameObject* objectB, Vector3D minTransUnit, meters minTransMag) {

    switch (objectA->getType()) {
        case ObjectType::Ball:
            ballReact(objectA, objectB, minTransUnit, minTransMag);
            break;
        case ObjectType::Wall:
            wallReact(objectA, objectB, minTransUnit, minTransMag);
            break;
        case ObjectType::Bullet:
            break;
        case ObjectType::Player:
            break;
        case ObjectType::None:
            noneReact(objectA, objectB, minTransUnit, minTransMag);
            break;
    }
}

void moveSetOfObjects(std::vector<GameObject*> gameObjects, seconds timestep, int level) {

    // move all objects
    for (GameObject* object : gameObjects) {
        moveObject(object, timestep);
    }

    // check for intersections
    vector<ObjectIntersection> intersections;

    for (size_t i = 0; i < gameObjects.size(); ++i) {

        for (size_t j = i+1; j < gameObjects.size(); ++j) {
            GameObject* objectA = gameObjects.at(i);
            GameObject* objectB = gameObjects.at(j);

            if (objectA->isStatic() && objectB->isStatic()) {
                continue;
            }

            if (objectA->getVelocity().magnitude() > objectB->getVelocity().magnitude()) {
                GameObject* temp = objectA;
                objectA = objectB;
                objectB = temp;
            }

            SatIntersection intersection = checkForIntersection(objectA, objectB);
            if (intersection.doesIntersect()) {
                intersections.push_back(ObjectIntersection(objectA, objectB, intersection));
            }
        }
    }

    // account for intersections
    if (intersections.size() > 0) {

        // check for multiway intersections
            // back up until only single intersections
        std::unordered_map<GameObject*,long> intersectionCount;
        for (ObjectIntersection& intersection : intersections) {

            if (intersectionCount.count(intersection.a)) { ++intersectionCount[intersection.a]; }
            else { intersectionCount.emplace(intersection.a, 1L); }

            if (intersectionCount.count(intersection.b)) { ++intersectionCount[intersection.b]; }
            else { intersectionCount.emplace(intersection.b, 1L); }
        }

        seconds miniStep = timestep / 10.0;
        if (miniStep > MIN_TIMESTEP) {

            std::unordered_set<GameObject *> multiIntersectionObjects;
            for (auto &count : intersectionCount) {
                if (count.second > 1) {
                    std::vector<ObjectIntersection>::iterator itr = intersections.begin();
                    while (itr != intersections.end()) {
                        ObjectIntersection &intersection = *itr;
                        if (intersection.a == count.first || intersection.b == count.first) {
                            multiIntersectionObjects.insert(intersection.a);
                            multiIntersectionObjects.insert(intersection.b);
                            itr = intersections.erase(itr);
                        } else {
                            ++itr;
                        }
                    }
                }
            }

            if (multiIntersectionObjects.size() > 0) {

                // move all objects back
                for (GameObject *object : multiIntersectionObjects) {
                    if (!object->isStatic()) {
                        moveObject(object, -timestep);
                    }
                }

                double tempTime = 0;
                while (tempTime < timestep) {
                    tempTime += miniStep;
                    moveSetOfObjects(
                            vector<GameObject *>(multiIntersectionObjects.begin(), multiIntersectionObjects.end()),
                            miniStep, level + 1);
                }
            }
        }

        std::unordered_set<GameObject*> movedObjects;

        // move each one back
        // change velocities
        // change animations
        for(ObjectIntersection& intersection : intersections) {

            GameObject* objectA = intersection.a;
            GameObject* objectB = intersection.b;

            // only intersect if object has not already been affected
            if (movedObjects.count(objectA) == 0 && movedObjects.count(objectB) == 0) {

                // rotate the MTV back into world coordinates
                Vector3D minTransUnit = objectA->getOrientation().getRotated(Vector3D(intersection.minTranslationUnit.x(), intersection.minTranslationUnit.y(), 0));
                react(objectA, objectB, minTransUnit, intersection.minTranslationMagnetidue);
                movedObjects.insert(objectA);
                movedObjects.insert(objectB);
            }
        }
    }
}

void LocalUpdatingWorld::update() {

    vector<Command> commands = CommandReceiver::getAndClearCommands();

    m_timeController.update();
    m_gameTime = m_timeController.get();
    seconds delta = m_timeController.getDelta();

    moveSetOfObjects(m_gameObjects, delta, 0);

    // update animations
    for (GameObject* object : m_gameObjects) {
        updateObjectAnimation(object, delta);
    }

    // fake load
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

} // BattleRoom namespace


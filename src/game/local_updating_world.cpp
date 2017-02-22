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

void updateObjectAnimation(GameObject& object, seconds timestep) {

    Animation& animation = object.getAnimation();
    seconds newState = object.getAnimationState() + timestep;

    if (newState > animation.getLength()) {

        // set the new state (time elapsed since end of last animation)
        object.setAnimationState(newState - animation.getLength());

        // find the new animation
        animation = AnimationHandler::getAnimation(animation.getNextAnimation());
    }
    else {

        // iterate object animation
        object.setAnimationState(newState);
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

//    Vector2D dist = Vector2D(
//                objectB->getLocation().x() - objectA->getLocation().x(),
//                objectB->getLocation().y() - objectA->getLocation().y()
//                );

    Vector3D apos = objectA->getLocation();
    Vector3D bpos = objectB->getLocation();
    Vector3D temp = bpos.minus(apos);

    Vector3D test = objectA->getOrientation().getInverseRotated(Vector3D(1,0,0));
    Vector3D test2 = objectA->getOrientation().getInverseRotated(Vector3D(0,1,0));
    Vector3D delta = objectA->getOrientation().getInverseRotated(objectB->getLocation().minus(objectA->getLocation()));
    Vector2D dist(delta.x(),delta.y());

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

            GameObject* a = intersection.a;
            GameObject* b = intersection.b;

            // A is the slower/static one
            Vector3D mtv_unit = a->getOrientation().getRotated(Vector3D(intersection.minTranslationUnit.x(), intersection.minTranslationUnit.y(), 0));
            Vector3D bOffset = mtv_unit.times(intersection.minTranslationMagnetidue);
            // TODO rotate bOffset and minTranslation unit by a's orientation

            if (movedObjects.count(a) == 0 && movedObjects.count(b) == 0) {

                Vector3D location = b->getLocation();
                location.x() = bOffset.x() + location.x();
                location.y() = bOffset.y() + location.y();
                b->setLocation(location);
                double elasticity = 0.9;

                if (a->isStatic()) {

                    double dx = b->getVelocity().x();
                    double dy = b->getVelocity().y();
                    double dz = b->getVelocity().z();
                    double vdotmtv = dx * mtv_unit.x() + dy * mtv_unit.y();

                    dx = dx - (1+elasticity) * vdotmtv * mtv_unit.x();
                    dy = dy - (1+elasticity) * vdotmtv * mtv_unit.y();

                    b->setVelocity(Vector3D(dx, dy, dz));
                    movedObjects.insert(b);
                }
                else {

                    double adx = a->getVelocity().x();
                    double ady = a->getVelocity().y();
                    double adz = a->getVelocity().z();
                    double bdx = b->getVelocity().x();
                    double bdy = b->getVelocity().y();
                    double bdz = b->getVelocity().z();
                    Vector2D mtv_unit = intersection.minTranslationUnit;
                    double vdotmtv = (adx-bdx)*mtv_unit.x() + (ady-bdy)*mtv_unit.y();

                    kilograms amass = a->getMass();
                    kilograms bmass = b->getMass();
                    meters newBx = (amass/(amass+bmass))*bOffset.x()/2.0;
                    meters newBy = (amass/(amass+bmass))*bOffset.y()/2.0;
                    meters newAx = -(bmass/(amass+bmass))*bOffset.x()/2.0;
                    meters newAy = -(bmass/(amass+bmass))*bOffset.y()/2.0;
                    double adxn = (bmass/(amass+bmass))*(1+elasticity)*vdotmtv*mtv_unit.x();
                    double adyn = (bmass/(amass+bmass))*(1+elasticity)*vdotmtv*mtv_unit.y();
                    a->setLocation(a->getLocation().minus(Vector3D(newAx,newAy,0)));
                    a->setVelocity(a->getVelocity().minus(Vector3D(adxn,adyn,adz)));
                    double bdxn = (amass/(amass+bmass))*(1+elasticity)*vdotmtv*mtv_unit.x();
                    double bdyn = (amass/(amass+bmass))*(1+elasticity)*vdotmtv*mtv_unit.y();
                    b->setLocation(b->getLocation().plus(Vector3D(newBx,newBy,0)));
                    b->setVelocity(b->getVelocity().plus(Vector3D(bdxn,bdyn,bdz)));
                    movedObjects.insert(a);
                    movedObjects.insert(b);
                }
            }
        }
    }
}

void LocalUpdatingWorld::update() {

    vector<Command> commands = CommandReceiver::getAndClearCommands();

    m_timeController.update();
    m_gameTime = m_timeController.get();
    seconds delta = m_timeController.getDelta();

    std::vector<GameObject*> objects;
    for (GameObject& obj : m_gameObjects) {
        objects.push_back(&obj);
    }

    moveSetOfObjects(objects, delta, 0);

    // update animations
    for (GameObject& object : m_gameObjects) {
        updateObjectAnimation(object, delta);
    }

    // fake load
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

} // BattleRoom namespace


#include "battle_room/game/local_updating_world.h"

#include "src/game/objects/object_intersection.h"

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
            : LocalUpdatingWorld() {
        applySettings(settings);
    }

    std::unordered_map<GameObject *, long> countObjectIntersections(vector<ObjectIntersection> intersections) {
        std::unordered_map<GameObject *, long> counts;
        for (ObjectIntersection &intersection : intersections) {

            if (counts.count(intersection.getObjectA())) {
                ++counts[intersection.getObjectA()];
            }
            else {
                counts.emplace(intersection.getObjectA(), 1L);
            }

            if (counts.count(intersection.getObjectB())) {
                ++counts[intersection.getObjectB()];
            }
            else {
                counts.emplace(intersection.getObjectB(), 1L);
            }
        }
        return counts;
    }

    // other functions

    void moveObject(GameObject *object, seconds timestep) {

        object->setPosition(object->getPosition().plus(object->getVelocity().times(timestep)));
        object->setRotation(object->getRotation() + timestep*object->getAngularVelocity());
    }

    void moveSetOfObjects(std::vector<GameObject *> gameObjects, seconds timestep) {

        // move all objects
        for (GameObject *object : gameObjects) {
            moveObject(object, timestep);
        }

        // check for intersections
        vector<ObjectIntersection> intersections = ObjectIntersection::getIntersections(gameObjects);

        if (intersections.size() > 0) {

            // if above min timestep, check for multi-intersections
            seconds miniStep = timestep / 10.0;
            if (miniStep > MIN_TIMESTEP) {

                std::unordered_map<GameObject *, long> counts = countObjectIntersections(intersections);

                // get set of multi-intersection objects
                std::unordered_set<GameObject *> multiObjects;
                for (auto &count : counts) {
                    if (count.second > 1) {

                        // remove it from normal intersections
                        std::vector<ObjectIntersection>::iterator itr = intersections.begin();
                        while (itr != intersections.end()) {

                            ObjectIntersection &intersection = *itr;
                            if (intersection.getObjectA() == count.first || intersection.getObjectB() == count.first) {

                                multiObjects.insert(intersection.getObjectA());
                                multiObjects.insert(intersection.getObjectB());
                                itr = intersections.erase(itr);
                            } else {
                                ++itr;
                            }
                        }
                    }
                }

                // if any multi-intersections, rerun but 10x slower
                if (multiObjects.size() > 0) {

                    for (GameObject *object : multiObjects) {
                        if (!object->isStatic()) {
                            moveObject(object, -timestep);
                        }
                    }

                    double tempTime = 0;
                    while (tempTime < timestep) {
                        tempTime += miniStep;
                        moveSetOfObjects(vector<GameObject *>(multiObjects.begin(), multiObjects.end()), miniStep);
                    }
                }
            }

            std::unordered_set<GameObject *> movedObjects;
            for (ObjectIntersection &intrct : intersections) {

                // only intersect if object has not already been affected
                if (movedObjects.count(intrct.getObjectA()) == 0 && movedObjects.count(intrct.getObjectB()) == 0) {

                    intrct.reactToCollision();
                    movedObjects.insert(intrct.getObjectA());
                    movedObjects.insert(intrct.getObjectB());
                }
            }
        }
    }

    std::vector<GameObject*> deleteDestroyed(std::vector<GameObject*> gameObjects) {
        std::vector<GameObject*> filtered;
        for (GameObject* obj : gameObjects) {
            if (obj->destroy()) {
                delete obj;
            }
            else {
                filtered.push_back(obj);
            }
        }
        return filtered;
    }

    void LocalUpdatingWorld::update() {

        // get user/ai input
        vector<Command> commands = CommandReceiver::getAndClearCommands();

        // tick game clock
        m_timeController.update();
        m_gameTime = m_timeController.get();
        seconds timestep = m_timeController.getDelta();

        // move objects, check for collisions, react to collisions
        moveSetOfObjects(m_gameObjects, timestep);

        // update animations
        for (GameObject *object : m_gameObjects) {
            object->updateAnimation(timestep);
            object->updateForNext(timestep);
        }

        m_gameObjects = deleteDestroyed(m_gameObjects);

        // fake load
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }

} // BattleRoom namespace


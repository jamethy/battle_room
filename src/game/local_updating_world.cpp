#include "battle_room/game/local_updating_world.h"

#include "src/game/objects/object_intersection.h"

#include "battle_room/game/command_receiver.h"

#include <iostream>
#include <map>
#include <cmath>

// temp for fake load
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>

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

        sub = settings.getSubResource("Boundary");
        if (isNotEmpty(sub.getValue())) {
            m_boundary = BoundarySet::createBoundary(sub);
        } // TODO else create one?
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

    void moveSetOfObjects(const std::vector<GameObject*>& gameObjects, seconds timestep) {

        // move all objects
        for (const auto& object : gameObjects) {
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
                        moveSetOfObjects(vector<GameObject*>(multiObjects.begin(), multiObjects.end()), miniStep);
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

    void LocalUpdatingWorld::update() {

        std::vector<GameObject*> addedObjects;

        // get user/ai input
        for (auto& cmd : CommandReceiver::getAndClearCommands()) {
            for (const auto& obj : m_gameObjects) {
                if (obj->interpretCommand(cmd)) {
                    std::vector<GameObject*> objects = obj->getAddedObjects();
                    addedObjects.insert(addedObjects.end(), objects.begin(), objects.end());
                    break;
                }
            }
        }

        // tick game clock
        m_timeController.update();
        m_gameTime = m_timeController.get();
        seconds timestep = m_timeController.getDelta();

        // move objects, check for collisions, react to collisions
        std::vector<GameObject*> rawPointers(m_gameObjects.size());
        rawPointers.clear();
        for (const auto& obj : m_gameObjects) {
            rawPointers.push_back(obj.get());
        }
        moveSetOfObjects(rawPointers, timestep);

        // update animations
        for (const auto& object : m_gameObjects) {
            object->updateAnimation(timestep);
            object->updateForNext(timestep);

        }

        // check boundary
        if (m_boundary != nullptr) {
            for (const auto& object : m_gameObjects) {
                if (!m_boundary->contains(object->getPosition())) {
                    object->setToDestroy(true);
                }
            } 
        } 

        // delete destroyed
        for (vector<UniqueGameObject>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();) {
            if ((*it)->destroy()) {
                it = m_gameObjects.erase(it);
            } else {
                ++it;
            }
        }

        // add added
        for (const auto& addedObj : addedObjects) {
            m_gameObjects.push_back(UniqueGameObject(addedObj));
        }

        // fake load
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

} // BattleRoom namespace


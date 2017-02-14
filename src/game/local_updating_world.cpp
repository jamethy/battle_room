#include "battle_room/game/local_updating_world.h"

#include "battle_room/common/unique_id.h"
#include "battle_room/common/animation_handler.h"
#include "battle_room/game/command_receiver.h"

#include <iostream>

// temp for fake load
#include <thread>
#include <chrono>

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

void moveObject(GameObject& object, seconds timestep) {
    object.setLocation( 
            object.getLocation()
            .plus(object.getVelocity().times(timestep) 
    ));
}

// other functions

void LocalUpdatingWorld::update() {

    vector<Command> commands = CommandReceiver::getAndClearCommands();

    m_timeController.update();
    m_gameTime = m_timeController.get();
    seconds delta = m_timeController.getDelta();

    // move all objects
    for (GameObject& object : m_gameObjects) {
        moveObject(object, delta);
    }

    // check for intersections
//    vector<pair<GameObject*,GameObject*>> intersections;
    vector<ObjectIntersection> intersections;

    for (int i = 0; i < m_gameObjects.size(); ++i) {
        for (int j = i+1; j < m_gameObjects.size(); ++j) {
            GameObject& objectA = m_gameObjects.at(i);
            GameObject& objectB = m_gameObjects.at(j);

            if (objectA.getUniqueId() == objectB.getUniqueId()) {
                continue;
            }

            if (objectA.isStatic() && objectB.isStatic()) {
                continue;
            }

            const BoundarySet& boundarySetA = objectA.getAnimation().getFrame(objectA.getAnimationState()).getBoundarySet();
            const BoundarySet& boundarySetB = objectA.getAnimation().getFrame(objectB.getAnimationState()).getBoundarySet();

            Vector2D dist = Vector2D( 
                    objectA.getLocation().x() - objectB.getLocation().x(), 
                    objectA.getLocation().y() - objectB.getLocation().y() 
            );

            bool intersects = false;
            for (Boundary* boundaryA : boundarySetA) {
                for (Boundary* boundaryB : boundarySetB) {

                    SatIntersection intersection = boundaryA->intersects(boundaryB, dist, 0);

                    if (intersection.doesIntersect()) {
                        intersects = true;
                        ObjectIntersection m(&objectA, &objectB, intersection);
                        intersections.push_back(m);
                        break;
                    }
                }
                if (intersects) {
                    break;
                }
            }
        }
    }

    // account for intersections
    if (intersections.size() > 0) {
        std::cout << "there were " << intersections.size() << " intersections.\n";

        // check for multiway intersections
            // back up until only single intersections

        // move each one back
        
        // change velocities
        // change animations
    }

    // update animations
    for (GameObject& object : m_gameObjects) {
        updateObjectAnimation(object, delta);
    }

    // fake load
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

} // BattleRoom namespace


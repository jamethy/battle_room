#include "battle_room/game/world.h"

#include "battle_room/common/unique_id.h"
#include "battle_room/common/animation_handler.h"

#include <iostream>

// temp
#include <thread>
#include <chrono>

using std::vector;

namespace BattleRoom {

// apply settings

void World::applySettings(ResourceDescriptor settings) {

    for (ResourceDescriptor& objDesc : settings.getSubResources("Object")) {
        GameObject obj(UniqueId::generateNewNetworkId());
        obj.applySettings(objDesc);
        m_gameObjects.push_back(obj);
    }

    ResourceDescriptor sub = settings.getSubResource("Time");
    if (isNotEmpty(sub.getValue())) {
        m_gameTime.set(toSeconds(sub.getValue()));
    }
}

// constructors
World::World() {
    m_gameObjects.clear();
}

World::World(ResourceDescriptor settings) 
    : World()
{
    applySettings(settings);
}

void updateGameObject(GameObject& object, seconds timestep) {

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

// other functions

void World::update() {

    m_gameTime.update();

    for (GameObject& object : m_gameObjects) {
        updateGameObject(object, m_gameTime.getDelta());
    }

    // fake load
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

vector<GameObject> World::getAllGameObjects() {
    return m_gameObjects;
}

// access by reference
GameTime& World::gameTime() {
    return m_gameTime;
}

} // BattleRoom namespace

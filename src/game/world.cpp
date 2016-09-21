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
        m_gameTime = toSeconds(sub.getValue());
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

vector<GameObject> World::getAllGameObjects() {
    return m_gameObjects;
}

seconds World::getGameTime() {
    return m_gameTime;
}

} // BattleRoom namespace

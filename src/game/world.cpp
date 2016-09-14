#include "battle_room/game/world.h"

#include "battle_room/common/unique_id.h"
#include "battle_room/common/animation_handler.h"

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


// other functions

void World::update() {

    m_gameTime.update();
}



vector<GameObject> World::getAllGameObjects() {
    return m_gameObjects;
}

} // BattleRoom namespace

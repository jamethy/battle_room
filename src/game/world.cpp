#include "battle_room/game/world.h"

#include "battle_room/common/unique_id.h"
#include "battle_room/common/animation_handler.h"
#include "battle_room/game/objects/ball.h"

using std::vector;

namespace BattleRoom {

// apply settings

void World::applySettings(ResourceDescriptor settings) {

    // TODO make a factory

    for (ResourceDescriptor& objDesc : settings.getSubResources("Object")) {
        GameObject* obj = new GameObject(UniqueId::generateNewNetworkId(), ObjectType::None);
        obj->applySettings(objDesc);
        m_gameObjects.push_back(obj);
    }

    for (ResourceDescriptor& objDesc : settings.getSubResources("Ball")) {
        GameObject* obj = new Ball(UniqueId::generateNewNetworkId());
        obj->applySettings(objDesc);
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

vector<GameObject*> World::getAllGameObjects() {
    return m_gameObjects;
}

seconds World::getGameTime() {
    return m_gameTime;
}

} // BattleRoom namespace

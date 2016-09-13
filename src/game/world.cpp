#include "battle_room/game/world.h"

#include "battle_room/common/unique_id.h"
#include "battle_room/common/animation_handler.h"

using std::vector;

namespace BattleRoom {

// apply settings

void World::applySettings(ResourceDescriptor settings) {

}

// constructors
World::World() {
    m_gameObjects.clear();

    GameObject obj(UniqueId::generateNewNetworkId());
    obj.setAnimation(AnimationHandler::getAnimation("boy_walking"));
    //Quaternion q;
    //q.rotateAboutZ(30.0*3.14159/180.0);
    //obj.setOrientation(q);

    m_gameObjects.push_back(obj);
}

World::World(ResourceDescriptor settings) 
    : World()
{
    applySettings(settings);
}


// other functions

vector<GameObject> World::getAllGameObjects() {
    return m_gameObjects;
}

} // BattleRoom namespace

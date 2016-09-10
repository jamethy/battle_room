#include "battle_room/game/world/game_world.h"
#include "battle_room/game/world/server_client_factory.h"

namespace BattleRoom {

// apply settings

void GameWorld::applySettings(ResourceDescriptor settings) {

    ResourceDescriptor sub = settings.getSubResource("Server");
    if (isNotEmpty(sub.getValue())) {
        m_serverClient = ServerClientFactory::createServerClient(sub);
    }
}

// constructors
GameWorld::GameWorld(ResourceDescriptor settings)
    : m_serverClient(ServerClientFactory::createEmptyServerClient())
{ 
    applySettings(settings);
}

} // BattleRoom namespace

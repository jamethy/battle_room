
#include "battle_room/networking/game_server.h"

namespace BattleRoom {

// apply settings

void GameServer::applySettings(ResourceDescriptor settings) {

    m_gameWorld.applySettings(settings.getSubResource("World"));
}

// constructors

GameServer::GameServer() {}

GameServer::GameServer(ResourceDescriptor settings)
    : GameServer()
{
    applySettings(settings);
}

} // namespace BattleRoom

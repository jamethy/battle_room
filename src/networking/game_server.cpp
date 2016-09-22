#include "battle_room/networking/game_server.h"

#include "battle_room/game/query_world.h"
#include "battle_room/game/command_receiver.h"

#include <chrono>

namespace BattleRoom {

void GameServer::applySettings(ResourceDescriptor settings) {

    // networking settings

}

void serverFunction(bool& keepGoing) {

    while (keepGoing) {

        // check for receiving message

            // if command message
                //CommandReceiver::addCommands(...);

            // look for server requests
                // respond to them with game stuff
                    // QueryWorld::getAllGameObjects();
                    // etc

        // fake load
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }
}

GameServer::GameServer(ResourceDescriptor settings) 
    : m_keepGoing(true)
{
    applySettings(settings);

    m_serverThread = std::thread(serverFunction,
            std::ref(m_keepGoing)
    );
}

GameServer::~GameServer() {
    m_keepGoing = false;
    if (m_serverThread.joinable()) {
        m_serverThread.join();
    }
}

} // BattleRoom namespace

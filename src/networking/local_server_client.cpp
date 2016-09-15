#include "battle_room/networking/local_server_client.h"

namespace BattleRoom {

// apply settings

void LocalServerClient::applySettings(ResourceDescriptor settings) {

    m_gameWorld.applySettings(settings.getSubResource("World"));
    m_middleWorld = m_gameWorld;

    updateBuffer();
}


// local threading function
void localThreadFunction(World& game, World& middle, std::mutex& worldLock, bool& keepGoing) {

    while (keepGoing) {
        game.update();
        worldLock.lock();
        middle = game;
        worldLock.unlock();
    }
}

// constructor
LocalServerClient::LocalServerClient(ResourceDescriptor settings) 
{
    m_updateWorldThread = std::thread(localThreadFunction, 
            std::ref(m_gameWorld), 
            std::ref(m_middleWorld),
            std::ref(m_middleWorldLock), 
            std::ref(m_keepThreadGoing));

    applySettings(settings);
}

LocalServerClient::~LocalServerClient() {
}

// other functions

void LocalServerClient::updateBuffer() {
    ServerClient::updateBuffer();
}
} // BattleRoom namespace

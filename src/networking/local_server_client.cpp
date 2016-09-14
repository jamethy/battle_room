#include "battle_room/networking/local_server_client.h"

namespace BattleRoom {

// apply settings

void LocalServerClient::applySettings(ResourceDescriptor settings) {


    m_updateWorldLock.lock();
    m_gameWorld.applySettings(settings.getSubResource("World"));
    m_updateWorldLock.unlock();

    updateBuffer();
}


// local threading function
void localThreadFunction(World& world, std::mutex& worldLock, bool& keepGoing) {

    while (keepGoing) {
        worldLock.lock();
        // update world
        worldLock.unlock();
    }
}

// constructor
LocalServerClient::LocalServerClient(ResourceDescriptor settings) 
{
    m_updateWorldThread = std::thread(localThreadFunction, 
            std::ref(m_gameWorld), 
            std::ref(m_updateWorldLock), 
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

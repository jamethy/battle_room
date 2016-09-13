#include "battle_room/networking/local_server_client.h"

namespace BattleRoom {

// apply settings

void LocalServerClient::applySettings(ResourceDescriptor settings) {


    m_updateWorldLock.lock();
    m_gameWorld.applySettings(settings.getSubResource("World"));
    m_updateWorldLock.unlock();

    updateBuffer();
}

void threadFunction(World& &world, std::mutex& worldLock, bool& keepGoing) {

        while (keepGoing) {
            worldLock.lock();
            // update world
            worldLock.unlock();
        }
}

// constructor
LocalServerClient::LocalServerClient(ResourceDescriptor settings) 
{
    m_updateWorldThread = std::thread(threadFunction, 
            std::ref(m_gameWorld), 
            std::ref(m_updateWorldLock), 
            std::ref(m_keepThreadGoing));

    applySettings(settings);
}

LocalServerClient::~LocalServerClient() {
    m_keepThreadGoing = false;
    m_updateWorldThread.join();
}

// other functions

void LocalServerClient::updateBuffer() {

    m_updateWorldLock.lock();
    m_queryWorld = m_gameWorld;
    m_updateWorldLock.unlock();

}


std::vector<GameObject> LocalServerClient::getAllGameObjects() { 
    return m_queryWorld.getAllGameObjects();
}

} // BattleRoom namespace

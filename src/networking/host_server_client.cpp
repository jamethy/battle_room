#include "battle_room/networking/host_server_client.h"

namespace BattleRoom {

// apply settings

void HostServerClient::applySettings(ResourceDescriptor settings) {

    // server object pass settings
    updateBuffer();
}

// host threading function
void hostThreadFunction(World& game, World& middle, std::mutex& worldLock, bool& keepGoing) {

    while (keepGoing) {
        
        // get updated from local server
        // set updated info in game world

        worldLock.lock();
        middle = game;
        worldLock.unlock();
    }
}

// constructor
HostServerClient::HostServerClient(ResourceDescriptor settings) 
{
    m_updateWorldThread = std::thread(hostThreadFunction, 
            std::ref(m_gameWorld), 
            std::ref(m_middleWorld), 
            std::ref(m_middleWorldLock), 
            std::ref(m_keepThreadGoing));

    applySettings(settings);
}

HostServerClient::~HostServerClient() {
}

// other functions

void HostServerClient::updateBuffer() {

    // send queued commands

    ServerClient::updateBuffer();
}
} // BattleRoom namespace

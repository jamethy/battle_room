#include "battle_room/networking/remote_server_client.h"

namespace BattleRoom {

// apply settings

void RemoteServerClient::applySettings(ResourceDescriptor settings) {

    // attempt connection with server
        // load game world from server

    updateBuffer();
}

// remote threading function
void remoteThreadFunction(World& world, std::mutex& worldLock, bool& keepGoing) {

    while (keepGoing) {

        // get updated info from server

        worldLock.lock();
        // set updated info in game world
        worldLock.unlock();
    }
}

// constructor
RemoteServerClient::RemoteServerClient(ResourceDescriptor settings) 
{
    m_updateWorldThread = std::thread(remoteThreadFunction, 
            std::ref(m_gameWorld), 
            std::ref(m_updateWorldLock), 
            std::ref(m_keepThreadGoing));

    applySettings(settings);
}

RemoteServerClient::~RemoteServerClient() {
}

// other functions

void RemoteServerClient::updateBuffer() {

    // send queued commands

    ServerClient::updateBuffer();
}

} // BattleRoom namespace

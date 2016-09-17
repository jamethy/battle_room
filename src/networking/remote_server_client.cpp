#include "battle_room/networking/remote_server_client.h"

namespace BattleRoom {

// apply settings

void RemoteServerClient::applySettings(ResourceDescriptor settings) {

    // attempt connection with server
        // load game world from server

    updateBuffer();
}

// remote threading function
void remoteThreadFunction(World& game, World& middle, std::mutex& worldLock, bool& keepGoing) {

    while (keepGoing) {

        // get updated info from server
        // set updated info in game world

        worldLock.lock();
        middle = game;
        worldLock.unlock();
    }
}

// constructor
RemoteServerClient::RemoteServerClient(ResourceDescriptor settings) 
{
    m_updateWorldThread = std::thread(remoteThreadFunction, 
            std::ref(m_gameWorld), 
            std::ref(m_middleWorld), 
            std::ref(m_middleWorldLock), 
            std::ref(m_keepThreadGoing));

    applySettings(settings);
}

RemoteServerClient::RemoteServerClient(const RemoteServerClient& original) 
    : ServerClient(original)
{ 
    m_updateWorldThread = std::thread(remoteThreadFunction, 
            std::ref(m_gameWorld), 
            std::ref(m_middleWorld),
            std::ref(m_middleWorldLock), 
            std::ref(m_keepThreadGoing));
}

RemoteServerClient::~RemoteServerClient() {
}

ServerClient* RemoteServerClient::clone() {
    return new RemoteServerClient(*this);
}

// other functions

void RemoteServerClient::updateBuffer() {

    // send queued commands

    ServerClient::updateBuffer();
}

} // BattleRoom namespace

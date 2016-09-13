#include "battle_room/networking/remote_server_client.h"

namespace BattleRoom {

// apply settings

void RemoteServerClient::applySettings(ResourceDescriptor settings) {

    // attempt connection with server
        // load game world from server

    updateBuffer();
}

// constructor
RemoteServerClient::RemoteServerClient(ResourceDescriptor settings) 
{
    applySettings(settings);
}

RemoteServerClient::~RemoteServerClient() {}

// other functions

void RemoteServerClient::updateBuffer() {

    // request game world mutex lock

    // copy game world to query world

    // release game world mutex lock

}


std::vector<GameObject> RemoteServerClient::getAllGameObjects() { 
    return m_queryWorld.getAllGameObjects();
}

} // BattleRoom namespace

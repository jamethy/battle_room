#include "battle_room/networking/host_server_client.h"

namespace BattleRoom {

// apply settings

void HostServerClient::applySettings(ResourceDescriptor settings) {

    // request game world mutex lock

    m_gameWorld.applySettings(settings.getSubResource("World"));

    // release game world mutex lock

    updateBuffer();
}

// constructor
HostServerClient::HostServerClient(ResourceDescriptor settings) 
{
    applySettings(settings);
}

HostServerClient::~HostServerClient() {}

// other functions

void HostServerClient::updateBuffer() {

    // request game world mutex lock

    // copy game world to query world

    // release game world mutex lock

}


std::vector<GameObject> HostServerClient::getAllGameObjects() { 
    return m_queryWorld.getAllGameObjects();
}

} // BattleRoom namespace

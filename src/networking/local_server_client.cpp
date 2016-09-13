#include "battle_room/networking/local_server_client.h"

namespace BattleRoom {

// apply settings

void LocalServerClient::applySettings(ResourceDescriptor settings) {

    // request game world mutex lock

    m_gameWorld.applySettings(settings.getSubResource("World"));

    // release game world mutex lock

    updateBuffer();
}

// constructor
LocalServerClient::LocalServerClient(ResourceDescriptor settings) 
{
    applySettings(settings);
}

LocalServerClient::~LocalServerClient() {}

// other functions

void LocalServerClient::updateBuffer() {

    // request game world mutex lock

    // copy game world to query world

    // release game world mutex lock

}


std::vector<GameObject> LocalServerClient::getAllGameObjects() { 
    return m_queryWorld.getAllGameObjects();
}

} // BattleRoom namespace

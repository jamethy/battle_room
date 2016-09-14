#include "battle_room/networking/server_client.h"

namespace BattleRoom {

// constructor
ServerClient::ServerClient() {
} 

ServerClient::~ServerClient() {
    m_keepThreadGoing = false;
    m_updateWorldThread.join();
}

// other functions

void ServerClient::updateBuffer() {
    m_updateWorldLock.lock();
    m_queryWorld = m_gameWorld;
    m_updateWorldLock.unlock();
}


std::vector<GameObject> ServerClient::getAllGameObjects() { 
    return m_queryWorld.getAllGameObjects();
}

} // BattleRoom namespace

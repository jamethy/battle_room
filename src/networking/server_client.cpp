#include "battle_room/networking/server_client.h"

namespace BattleRoom {

// constructors
ServerClient::ServerClient() {
} 

ServerClient::~ServerClient() {
    m_keepThreadGoing = false;
    if (m_updateWorldThread.joinable()) {
        m_updateWorldThread.join();
    }
}

// other functions

void ServerClient::updateBuffer() {
    m_middleWorldLock.lock();
    m_queryWorld = m_middleWorld;
    m_middleWorldLock.unlock();
}


std::vector<GameObject> ServerClient::getAllGameObjects() { 
    return m_queryWorld.getAllGameObjects();
}

} // BattleRoom namespace

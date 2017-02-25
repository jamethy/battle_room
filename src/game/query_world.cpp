#include "battle_room/game/query_world.h"

#include <mutex>

namespace BattleRoom {

World m_copyWorld; ///< World to constantly update
World m_queryWorld; ///< World to get info from
std::mutex m_copyWorldLock; ///< Lock for m_gameWorld reading/writing

void QueryWorld::updateBuffer() {
    m_copyWorldLock.lock();
    m_queryWorld = m_copyWorld;
    m_copyWorldLock.unlock();
}

void QueryWorld::updateCopyWorld(const World& world) {
    m_copyWorldLock.lock();
    m_copyWorld = world;
    m_copyWorldLock.unlock();
}

std::vector<GameObject*> QueryWorld::getAllGameObjects() {
    return m_queryWorld.getAllGameObjects();
}

} // BattleRoom namespace

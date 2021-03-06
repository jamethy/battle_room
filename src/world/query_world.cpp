#include "world/query_world.h"
#include "world/player.h"

#include <mutex>

namespace BattleRoom {

    World m_copyWorld; ///< World to constantly update
    World m_queryWorld; ///< World to get info from
    std::mutex m_copyWorldLock; ///< Lock for m_gameWorld reading/writing
    std::mutex m_queryWorldLock; ///< Lock for m_gameWorld reading/writing
    UniqueId m_clientId = UniqueId::generateInvalidId();

    void QueryWorld::updateBuffer() {
        m_copyWorldLock.lock();
        m_queryWorldLock.lock();
        m_queryWorld = m_copyWorld.clone();
        m_copyWorldLock.unlock();
        m_queryWorldLock.unlock();
    }

    void QueryWorld::updateCopyWorld(const World &world) {
        m_copyWorldLock.lock();
        m_copyWorld = world.clone();
        m_copyWorldLock.unlock();
    }

    void QueryWorld::copyTo(World *world) {
        m_queryWorldLock.lock();
        world->copy(m_queryWorld);
        m_queryWorldLock.unlock();
    }

    const std::vector<UniqueGameObject>& QueryWorld::getAllGameObjects() {
        return m_queryWorld.getAllGameObjects();
    }

    const GameObject* QueryWorld::getGameObject(UniqueId id) {
        return m_queryWorld.getGameObject(id);
    }

    const GameObject* QueryWorld::getClientPlayer() {
        for (const auto& obj : m_queryWorld.getAllGameObjects()) {
            if (ObjectType::Player == obj->getType()) {
                Player* player = (Player*)obj.get();
                if (player->getClient() == m_clientId) {
                    return player;
                }
            }
        }
        return nullptr;
    }

    const std::vector<UniqueDrawableObject>& QueryWorld::getBackgroundObjects() {
        return m_queryWorld.getBackgroundObjects();
    }

    const GameObject* QueryWorld::findIntersectingObject(Vector2D point) {
        return m_queryWorld.findIntersectingObject(point);
    }

    void QueryWorld::serialize(BinaryStream& bs) {
        m_queryWorldLock.lock();
        m_queryWorld.serialize(bs);
        m_queryWorldLock.unlock();
    }

    void QueryWorld::setClientId(UniqueId id) {
        m_clientId = id;
    }

    const UniqueId QueryWorld::getClientId() {
        return m_clientId;
    }

} // BattleRoom namespace

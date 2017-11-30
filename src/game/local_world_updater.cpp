#include "battle_room/game/local_world_updater.h"
#include "battle_room/game/query_world.h"
#include "battle_room/game/alter_world.h"
#include "battle_room/game/objects/object_factory.h"
#include "battle_room/game/objects/player.h"

#include <algorithm>

namespace BattleRoom {

    // apply settings
    void LocalWorldUpdater::applySettings(ResourceDescriptor settings) {
        m_world.applySettings(settings.getSubResource("World"));
        QueryWorldUpdater::applySettings(settings);
    }

    void worldUpdaterFunction(LocalUpdatingWorld &world, bool &keepUpdating, LocalWorldUpdater& updater) {

        while (keepUpdating) {
            world.update();
            QueryWorld::updateCopyWorld(world);
            updater.afterUpdate();
        }
    }

    void LocalWorldUpdater::start() {
        if (!m_keepUpdating) {
            m_keepUpdating = true;
            m_worldThread = std::thread(worldUpdaterFunction,
                    std::ref(m_world),
                    std::ref(m_keepUpdating),
                    std::ref(*this)
                    );
        }
    }

    LocalWorldUpdater::LocalWorldUpdater(ResourceDescriptor settings) : 
        m_keepUpdating(false) 
    { 
        applySettings(settings);
        start();
    }

    LocalWorldUpdater::LocalWorldUpdater() : 
        m_keepUpdating(false) 
    { }

    LocalWorldUpdater::~LocalWorldUpdater() {
        m_keepUpdating = false; //TODO make this an atomic boolean
        if (m_worldThread.joinable()) {
            m_worldThread.join();
        }
    }

    void LocalWorldUpdater::afterUpdate() {
        m_world.applySettings(m_worldUpdates);
        m_worldUpdates = ResourceDescriptor();

        AlterWorld::update(m_world);
    }

    void LocalWorldUpdater::registerUser(User user) {
        const UniqueId userId = user.getUniqueId();

        unregisterUser(userId);
        m_users.push_back(user);

        if (user.getUniqueId().isLocal()) {
            QueryWorld::setClientId(userId);
        }

        UniqueGameObject obj = ObjectFactory::createObjectOfType(ObjectType::Player);
        Player* player = (Player*)obj.get();
        player->setClient(userId);

        // TODO create spawning rules
        player->setPosition(Vector2D(-15, 15));
        player->setVelocity(Vector2D(5, 0));

        AlterWorld::addObject(std::move(obj));
    }

    std::vector<User>::iterator findIn(std::vector<User>& users, UniqueId id) {
        std::vector<User>::iterator itr;
        for (itr = users.begin(); itr != users.end(); ++itr) {
            if ((*itr).getUniqueId() == id) {
                return itr;
            }
        }
        return users.end();
    }

    void LocalWorldUpdater::unregisterUser(UniqueId userId) {
        auto itr = findIn(m_users, userId);
        if (itr != m_users.end()) {
            m_users.erase(itr);
        }
    }

} // BattleRoom namespace

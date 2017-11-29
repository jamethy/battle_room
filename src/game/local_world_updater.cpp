#include "battle_room/game/local_world_updater.h"
#include "battle_room/game/query_world.h"

namespace BattleRoom {

// apply settings
    void LocalWorldUpdater::applySettings(ResourceDescriptor settings) {

        m_world.applySettings(settings.getSubResource("World"));
    }

    void worldUpdaterFunction(LocalUpdatingWorld &world, bool &keepUpdating, LocalWorldUpdater& updater) {

        while (keepUpdating) {
            world.update();
            QueryWorld::updateCopyWorld(world);
            updater.afterUpdate();
        }
    }

// constructors
    LocalWorldUpdater::LocalWorldUpdater(ResourceDescriptor settings)
            : m_keepUpdating(true) {
        applySettings(settings);

        m_worldThread = std::thread(worldUpdaterFunction,
                                    std::ref(m_world),
                                    std::ref(m_keepUpdating),
                                    std::ref(*this)
        );
    }

    LocalWorldUpdater::~LocalWorldUpdater() {
        m_keepUpdating = false; //TODO make this an atomic boolean
        if (m_worldThread.joinable()) {
            m_worldThread.join();
        }
    }

    void LocalWorldUpdater::afterUpdate() {
    }

} // BattleRoom namespace

#include "battle_room/game/query_world_updater.h"

namespace BattleRoom {

    void QueryWorldUpdater::applySettings(ResourceDescriptor settings) { 
        ResourceDescriptor sub = settings.getSubResource("User");
        if (isNotEmpty(sub.getValue())) {
            registerUser(User(sub));
        }
    }

    QueryWorldUpdater::~QueryWorldUpdater() {
    }

    void QueryWorldUpdater::clientUpdate() {
    }

    void QueryWorldUpdater::registerUser(User user) {
        (void) user; // unused
    }
    void QueryWorldUpdater::unregisterUser(UniqueId userId) {
        (void) userId; // unused
    }

    const UniqueId QueryWorldUpdater::getUniqueId() const {
        return m_uniqueId;
    }
} // BattleRoom namespace

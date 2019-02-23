#include "world/query_world_updater.h"
#include "query_world_updater.h"


namespace BattleRoom {

    void QueryWorldUpdater::applySettings(ResourceDescriptor settings) {
        (void) settings; // unused
    }

    ResourceDescriptor QueryWorldUpdater::getSettings() const {
        ResourceDescriptor rd("WorldUpdater", "");
        rd.emplaceSubResource("UniqueId", m_uniqueId.toString());
        return rd;
    }

    QueryWorldUpdater::~QueryWorldUpdater() = default;

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

    bool QueryWorldUpdater::start() {
        return true;

    }
} // BattleRoom namespace

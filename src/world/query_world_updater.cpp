#include "world/query_world_updater.h"

namespace BattleRoom {

    void QueryWorldUpdater::applySettings(ResourceDescriptor settings) { 
        ResourceDescriptor sub = settings.getSubResource("User");
        if (isNotEmpty(sub.getValue())) {
            registerUser(User(sub));
        }
    }

    ResourceDescriptor QueryWorldUpdater::getSettings() const {
        ResourceDescriptor rd("WorldUpdater", "Empty");
        std::vector<ResourceDescriptor> subs = {};
        subs.emplace_back("UniqueId", m_uniqueId.toString());
        rd.setSubResources(subs);
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
} // BattleRoom namespace

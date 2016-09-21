#ifndef LOCAL_WORLD_UPDATER_H
#define LOCAL_WORLD_UPDATER_H

#include "battle_room/game/query_world_updater.h"
#include "battle_room/game/local_updating_world.h"

#include <thread>

namespace BattleRoom {

class LocalWorldUpdater : public QueryWorldUpdater {

public:

    LocalWorldUpdater(ResourceDescriptor settings);
    ~LocalWorldUpdater();

    // inherited
    void applySettings(ResourceDescriptor settings);

private:

    LocalUpdatingWorld m_world;
    std::thread m_worldThread;
    bool m_keepUpdating;

}; // LocalWorldUpdater
} // BattleRoom namespace
#endif // LOCAL_WORLD_UPDATER_H

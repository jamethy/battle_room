#ifndef LOCAL_WORLD_UPDATER_H
#define LOCAL_WORLD_UPDATER_H

#include "battle_room/game/query_world_updater.h"
#include "battle_room/game/local_updating_world.h"

#include <thread>

namespace BattleRoom {

/**
 * Implmentation of queryWorldUpdater for locally run or hosted games
 * Updates a LocalUpdatingWorld on a thread and copies that to the QueryWorld
 * Gets commands directly from CommandReciever
 */
class LocalWorldUpdater : public QueryWorldUpdater {

public:

    // constructors
    LocalWorldUpdater(ResourceDescriptor settings);
    ~LocalWorldUpdater();

    // inherited
    void applySettings(ResourceDescriptor settings);

private:

    LocalUpdatingWorld m_world; ///< World that updates itself
    std::thread m_worldThread; ///< Thread to update world on
    bool m_keepUpdating; ///< Set to false when ready to destroy

}; // LocalWorldUpdater
} // BattleRoom namespace
#endif // LOCAL_WORLD_UPDATER_H

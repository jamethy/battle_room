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
        virtual ~LocalWorldUpdater();

        virtual void afterUpdate();
        virtual void registerUser(User user) override;
        virtual void unregisterUser(UniqueId userId) override;

        // inherited
        virtual void applySettings(ResourceDescriptor settings) override;

    private:

        std::vector<User> m_users;

        LocalUpdatingWorld m_world; ///< World that updates itself
        std::thread m_worldThread; ///< Thread to update world on
        bool m_keepUpdating; ///< Set to false when ready to destroy

    }; // LocalWorldUpdater
} // BattleRoom namespace
#endif // LOCAL_WORLD_UPDATER_H

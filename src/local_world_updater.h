#ifndef LOCAL_WORLD_UPDATER_H
#define LOCAL_WORLD_UPDATER_H

#include "query_world_updater.h"
#include "local_updating_world.h"

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
        LocalWorldUpdater();

        explicit LocalWorldUpdater(ResourceDescriptor settings);

        void start();

        ~LocalWorldUpdater() override;

        virtual void afterUpdate();

        void registerUser(User user) override;

        void unregisterUser(UniqueId userId) override;

        // inherited
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    protected:

        std::vector<User> m_users;
        ResourceDescriptor m_worldUpdates;

    private:

        LocalUpdatingWorld m_world; ///< World that updates itself
        std::thread m_worldThread; ///< Thread to update world on
        bool m_keepUpdating; ///< Set to false when ready to destroy

    }; // LocalWorldUpdater
} // BattleRoom namespace
#endif // LOCAL_WORLD_UPDATER_H

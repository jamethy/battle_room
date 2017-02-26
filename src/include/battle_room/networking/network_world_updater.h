#ifndef NETWORK_WORLD_UPDATER_H
#define NETWORK_WORLD_UPDATER_H

#include "battle_room/game/query_world_updater.h"
#include "battle_room/game/world.h"

#include <thread>

namespace BattleRoom {

    class NetworkWorldUpdater : public QueryWorldUpdater {

    public:

        NetworkWorldUpdater(ResourceDescriptor settings);

        ~NetworkWorldUpdater();

        // inherited
        void applySettings(ResourceDescriptor settings);

    private:

        World m_world;
        std::thread m_worldThread;
        bool m_keepUpdating;

    }; // NetworkWorldUpdater
} // BattleRoom namespace
#endif // NETWORK_WORLD_UPDATER_H

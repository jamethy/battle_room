#ifndef BATTLE_ROOM_WORLD_UPDATER_FACTORY_H
#define BATTLE_ROOM_WORLD_UPDATER_FACTORY_H

#include "world/query_world_updater.h"

namespace BattleRoom {

    class WorldUpdaterFactory {

    public:

        static UniqueWorldUpdater createWorldUpdater(ResourceDescriptor settings);

        /**
         * \breif Creates a motionless camera
         * \return Unique Pointer to a Camera instance
         */
        static UniqueWorldUpdater createEmptyUpdater();


    }; // WorldUpdaterFactory class
} // BattleRoom namespace
#endif // BATTLE_ROOM_WORLD_UPDATER_FACTORY_H

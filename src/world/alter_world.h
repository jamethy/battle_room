#ifndef BATTLE_ROOM_ALTER_WORLD_H
#define BATTLE_ROOM_ALTER_WORLD_H

#include "world/local_updating_world.h"

namespace BattleRoom {

    class AlterWorld {

        public:

            static void addObject(UniqueGameObject object);

            static void update(LocalUpdatingWorld& world);

    }; // AlterWorld class
} // BattleRoom namespace
#endif // BATTLE_ROOM_ALTER_WORLD_H

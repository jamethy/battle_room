#ifndef ALTER_WORLD_H
#define ALTER_WORLD_H

#include "battle_room/game/local_updating_world.h"

namespace BattleRoom {

    class AlterWorld {

        public:

            static void addObject(UniqueGameObject object);

            static void update(LocalUpdatingWorld& world);

    }; // AlterWorld class
} // BattleRoom namespace
#endif // ALTER_WORLD_H

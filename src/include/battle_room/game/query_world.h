#ifndef QUERY_WORLD_H
#define QUERY_WORLD_H

#include "battle_room/game/world.h"

namespace BattleRoom {

class QueryWorld {

public:

    /**
     * \brief Updates the query world buffer from the game world buffer
     * May also send any commands etc.
     */
    static void updateBuffer();

    static void updateCopyWorld(const World& world);

    /**
     * Likely a temp function that returns all the game objects in the world
     */
    static std::vector<GameObject> getAllGameObjects();

}; // QueryWorld class
} // BattleRoom namespace
#endif // QUERY_WORLD_H

#ifndef BATTLE_ROOM_QUERY_WORLD_H
#define BATTLE_ROOM_QUERY_WORLD_H

#include "world/world.h"

namespace BattleRoom {

    /**
     * Singleton layer on top of static copies of the world that can be queried
     * with thread safety.
     */
    class QueryWorld {

    public:

        /**
         * \brief Updates the query world buffer from the game world buffer
         * May also send any commands etc.
         */
        static void updateBuffer();

        /**
         * \brief Copies the parameter into the query world
         * \param world World to copy into the query worldt
         */
        static void updateCopyWorld(const World &world);

        static void copyTo(World *world);

        static void serialize(BinaryStream& bs);

        // functions that need to be on on game interface thread

        /**
         * Likely a temp function that returns all the game objects in the world
         */
        static const std::vector<UniqueGameObject>& getAllGameObjects();

        static const GameObject* getGameObject(UniqueId id);
        static const GameObject* getClientPlayer();

        static const std::vector<UniqueDrawableObject>& getBackgroundObjects();

        static const GameObject* findIntersectingObject(Vector2D point);

        static void setClientId(UniqueId id);
        static const UniqueId getClientId();

    }; // QueryWorld class
} // BattleRoom namespace
#endif // BATTLE_ROOM_QUERY_WORLD_H

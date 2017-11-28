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

        /*
         * \brief Copies the parameter into the query world
         * \param world World to copy into the query world
         */
        static void updateCopyWorld(const World &world);

        /**
         * Likely a temp function that returns all the game objects in the world
         */
        static const std::vector<UniqueGameObject>& getAllGameObjects();

        static const GameObject* getGameObject(UniqueId id);

        static const std::vector<UniqueDrawableObject>& getBackgroundObjects();

        static const GameObject* findIntersectingObject(Vector2D point);

        static void serialize(BinaryStream& bs);

    }; // QueryWorld class
} // BattleRoom namespace
#endif // QUERY_WORLD_H

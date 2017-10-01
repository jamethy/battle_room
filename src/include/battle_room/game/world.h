#ifndef WORLD_H
#define WORLD_H

#include "battle_room/common/resource.h"
#include "battle_room/game/game_object.h"

#include <vector>

namespace BattleRoom {

/**
 * Game world - includes all the objects, the time, and meta data
 */
    class World : public Resource {

    public:

        // constructors
        World();
        World(const World& other);

        World(ResourceDescriptor settings);

        std::vector<GameObject *> getAllGameObjects(); // TEMP

        // getters
        seconds getGameTime();

        // inherited
        virtual void applySettings(ResourceDescriptor settings) override;

    protected:

        std::vector<GameObject *> m_gameObjects; // walls, stars, etc
        seconds m_gameTime; // Time in game


    }; // World class
} // BattleRoom namespace
#endif // WORLD_H

#ifndef WORLD_H
#define WORLD_H

#include "battle_room/common/resource.h"
#include "battle_room/game/game_object.h"
#include "battle_room/game/game_time.h"

#include <vector>

namespace BattleRoom {

/**
 * Game world - includes all the objects, the time, and meta data
 */
class World : public Resource {

public:

    // constructors
    World();
    World(ResourceDescriptor settings);

    /**
     * Update everything in the world. This will iterate the time
     * and updating everything else accordingly.
     */
    void update();

    std::vector<GameObject> getAllGameObjects(); // TEMP

    // access by reference
    GameTime& gameTime();

    // inherited
    void applySettings(ResourceDescriptor settings) override;

private:

    std::vector<GameObject> m_gameObjects; // TEMP
    GameTime m_gameTime; // Game time object

}; // World class
} // BattleRoom namespace
#endif // WORLD_H

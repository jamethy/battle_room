#ifndef WORLD_H
#define WORLD_H

#include "battle_room/common/resource.h"
#include "battle_room/game/game_object.h"
#include "battle_room/game/game_time.h"

#include <vector>

namespace BattleRoom {

class World : public Resource {

public:

    // constructors
    World();
    World(ResourceDescriptor settings);

    void update();

    std::vector<GameObject> getAllGameObjects(); // TEMP

    // inherited
    void applySettings(ResourceDescriptor settings) override;

private:

    std::vector<GameObject> m_gameObjects; // TEMP
    GameTime m_gameTime;

}; // World class
} // BattleRoom namespace
#endif // WORLD_H

#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include "battle_room/common/resource.h"
#include "battle_room/game/world.h"

namespace BattleRoom {

class GameServer : public Resource {

public:
    
    // constructors
    GameServer();
    GameServer(ResourceDescriptor settings);


    // inherited
    void applySettings(ResourceDescriptor settings) override;

private:

    World m_gameWorld; ///< The game world 

}; // GameServer
} // BattleRoom namespace
#endif // GAME_SERVER_H

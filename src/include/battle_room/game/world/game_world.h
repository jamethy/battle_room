#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include "battle_room/common/resource.h"
#include "battle_room/game/world/server_client.h"

namespace BattleRoom {

class GameWorld : Resource {

public:

    // constructors
    GameWorld(ResourceDescriptor settings);

    // send commands

    // inherited
    void applySettings(ResourceDescriptor settings);

private:

    UniqueServerClient m_serverClient; ///< Connection to the server object

    // Game World Server interface
        // contains current game state (and blocking ability)
        // Contains server connection

    // Game WOrld local interface (single player / maybe local host)
        // direct connect to server

    // Server
        // contains two game states
            // one for requests
            // one for updating
        // can send full game state
        // can send updates
        // can send partial game state
        // has time
        // receives commands
        // does physics
        // does 

        // process is
            // look at received commands and adjust
                // player states
                // new objects such as bullets
                // new velocity vectors
            // update time
            // update physics
            

    // There is a local state of everything
        // world objects
            // pos, velocity, animation etc.
        // Players
            // name, stats
            // status, current command?
    
    // Server Requests
        // full game state from server
        // game updates
        // partial game state based on unique ids
        // send commands

    // TODO test copying child object to base object


}; // GameWorld class
} // BattleRoom namespace
#endif // GAME_WORLD_H

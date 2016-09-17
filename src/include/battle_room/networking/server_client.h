#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include "battle_room/common/resource.h"
#include "battle_room/game/game_object.h"
#include "battle_room/game/world.h"

#include <memory>
#include <vector>
#include <thread>
#include <mutex>

namespace BattleRoom {

/**
 * ServerClient is the client's side of the link between the server and the client. 
 * Each server has two copies of the world: one it uses for updating on another thread 
 * (inside the class) and the other is used for querying from outside the class. The 
 * various implementations of ServerClient * update the game world in different ways 
 * and send requests to the actual server in different ways.
 */
class ServerClient : public Resource {

public:

    // constructors
    virtual ~ServerClient();
    virtual ServerClient* clone() = 0;

    /**
     * \brief Updates the query world buffer from the game world buffer
     * May also send any commands etc.
     */
    virtual void updateBuffer();

    /**
     * Likely a temp function that returns all the game objects in the world
     */
    virtual std::vector<GameObject> getAllGameObjects();

protected:

    ServerClient(); ///< Protected constructor, should create from ServerClientFactory
    ServerClient(const ServerClient& original);

    World m_gameWorld; ///< World to constantly update
    World m_middleWorld; ///< World to copy between
    World m_queryWorld; ///< World to get info from
    std::mutex m_middleWorldLock; ///< Lock for m_gameWorld reading/writing
    std::thread m_updateWorldThread; ///< thread for updating m_gameWorld
    bool m_keepThreadGoing = true; ///< Set to false when to stop updating m_gameWorld

}; // ServerClient class

/**
 * Unique pointer of a ServerClient. This should be created
 * using the ServerClientFactory.
 */
typedef std::unique_ptr<ServerClient> UniqueServerClient;

} // BattleRoom namespace
#endif // SERVER_CLIENT_H

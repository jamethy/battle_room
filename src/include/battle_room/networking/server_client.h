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

class ServerClient : public Resource {

public:

    // destructor
    virtual ~ServerClient();

    virtual void updateBuffer();

    virtual std::vector<GameObject> getAllGameObjects();

protected:

    ServerClient();

    World m_gameWorld; ///< World to constantly update
    World m_queryWorld; ///< World to get info from
    std::mutex m_updateWorldLock; ///< Lock for m_gameWorld reading/writing
    std::thread m_updateWorldThread; ///< thread for updating m_gameWorld
    bool m_keepThreadGoing = true; ///< Set to false when to stop updating m_gameWorld

}; // ServerClient class


typedef std::unique_ptr<ServerClient> UniqueServerClient;

} // BattleRoom namespace
#endif // SERVER_CLIENT_H

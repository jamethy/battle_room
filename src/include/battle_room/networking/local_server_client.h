#ifndef LOCAL_SERVER_CLIENT_H
#define LOCAL_SERVER_CLIENT_H

#include "battle_room/networking/server_client.h"
#include "battle_room/game/world.h"

#include <mutex>
#include <thread>

namespace BattleRoom {

class LocalServerClient : public ServerClient {

public:

    // constructor
    LocalServerClient(ResourceDescriptor settings);
    ~LocalServerClient() override;

    // inherited
    void updateBuffer() override;
    std::vector<GameObject> getAllGameObjects() override;
    void applySettings(ResourceDescriptor settings) override;
private:

    World m_gameWorld; ///< Game world
    World m_queryWorld; ///< Game world
    std::mutex m_updateWorldLock;
    std::thread m_updateWorldThread;
    bool m_keepThreadGoing = true;

}; // LocalServerClient class
} // BattleRoom namespace
#endif // LOCAL_SERVER_CLIENT_H

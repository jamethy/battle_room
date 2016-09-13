#ifndef LOCAL_SERVER_CLIENT_H
#define LOCAL_SERVER_CLIENT_H

#include "battle_room/networking/server_client.h"
#include "battle_room/game/world.h"

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

}; // LocalServerClient class
} // BattleRoom namespace
#endif // LOCAL_SERVER_CLIENT_H

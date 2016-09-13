#ifndef HOST_SERVER_CLIENT_H
#define HOST_SERVER_CLIENT_H

#include "battle_room/networking/server_client.h"

#include <memory>
#include <vector>

namespace BattleRoom {

class HostServerClient : public ServerClient {

public:

    // destructor
    HostServerClient(ResourceDescriptor settings);
    ~HostServerClient() override;

    // inherited
    void updateBuffer() override;
    std::vector<GameObject> getAllGameObjects() override;
    void applySettings(ResourceDescriptor settings) override;

private:

    World m_queryWorld; ///< Game world used for interface query
    World m_gameWorld; ///< Game world


}; // HostServerClient class
} // BattleRoom namespace
#endif // HOST_SERVER_CLIENT_H

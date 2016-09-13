#ifndef REMOTE_SERVER_CLIENT_H
#define REMOTE_SERVER_CLIENT_H

#include "battle_room/networking/server_client.h"

#include <memory>
#include <vector>

namespace BattleRoom {

class RemoteServerClient : public ServerClient {

public:

    // destructor
    RemoteServerClient(ResourceDescriptor settings);
    ~RemoteServerClient() override;

    // inherited
    void updateBuffer() override;
    std::vector<GameObject> getAllGameObjects() override;
    void applySettings(ResourceDescriptor settings) override;

private:

    World m_queryWorld; ///< Game world used for interface query
    World m_gameWorld; ///< Game world


}; // RemoteServerClient class
} // BattleRoom namespace
#endif // REMOTE_SERVER_CLIENT_H

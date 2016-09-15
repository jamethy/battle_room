#ifndef REMOTE_SERVER_CLIENT_H
#define REMOTE_SERVER_CLIENT_H

#include "battle_room/networking/server_client.h"

namespace BattleRoom {

/**
 * Implementation of ServerClient for a typically player joining a networked game.
 * It queries the server for info on another thread, updating the gameWorld and then
 * makes those changes available during updateBuffer
 */
class RemoteServerClient : public ServerClient {

public:

    // constructors
    RemoteServerClient(ResourceDescriptor settings);
    virtual ~RemoteServerClient() override;

    // inherited
    virtual void updateBuffer() override;
    virtual void applySettings(ResourceDescriptor settings) override;

}; // RemoteServerClient class
} // BattleRoom namespace
#endif // REMOTE_SERVER_CLIENT_H

#ifndef REMOTE_SERVER_CLIENT_H
#define REMOTE_SERVER_CLIENT_H

#include "battle_room/networking/server_client.h"

namespace BattleRoom {

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

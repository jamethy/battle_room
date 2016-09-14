#ifndef HOST_SERVER_CLIENT_H
#define HOST_SERVER_CLIENT_H

#include "battle_room/networking/server_client.h"

namespace BattleRoom {

class HostServerClient : public ServerClient {

public:

    // destructor
    HostServerClient(ResourceDescriptor settings);
    ~HostServerClient() override;

    // inherited
    void updateBuffer() override;
    void applySettings(ResourceDescriptor settings) override;

private:

    // server object

}; // HostServerClient class
} // BattleRoom namespace
#endif // HOST_SERVER_CLIENT_H

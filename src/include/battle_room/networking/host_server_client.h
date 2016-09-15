#ifndef HOST_SERVER_CLIENT_H
#define HOST_SERVER_CLIENT_H

#include "battle_room/networking/server_client.h"

namespace BattleRoom {

/**
 * HostServerClient is for hosting locally but playing with others. This will
 * most likely somehow join with remote and also contain a server... once I make 
 * a server class...
 */
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

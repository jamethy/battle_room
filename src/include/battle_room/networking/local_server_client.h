#ifndef LOCAL_SERVER_CLIENT_H
#define LOCAL_SERVER_CLIENT_H

#include "battle_room/networking/server_client.h"

namespace BattleRoom {

/**
 * An implementation of ServerClient that has a 'server' within it without 
 * all the networking stuff involved. It basically just updates the world on
 * another thread.
 */
class LocalServerClient : public ServerClient {

public:

    // constructor
    LocalServerClient(ResourceDescriptor settings);
    ~LocalServerClient() override;

    // inherited
    void updateBuffer() override;
    void applySettings(ResourceDescriptor settings) override;

}; // LocalServerClient class
} // BattleRoom namespace
#endif // LOCAL_SERVER_CLIENT_H

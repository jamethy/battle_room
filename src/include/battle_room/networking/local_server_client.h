#ifndef LOCAL_SERVER_CLIENT_H
#define LOCAL_SERVER_CLIENT_H

#include "battle_room/networking/server_client.h"

namespace BattleRoom {

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

#ifndef SERVER_CLIENT_FACTORY_H
#define SERVER_CLIENT_FACTORY_H

#include "battle_room/networking/server_client.h"

namespace BattleRoom {

class ServerClientFactory {

public:

    static UniqueServerClient createServerClient(ResourceDescriptor settings);

    static UniqueServerClient createEmptyServerClient();

}; // ServerClientFactory class
} // BattleRoom namespace
#endif // SERVER_CLIENT_FACTORY_H

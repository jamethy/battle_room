#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include "battle_room/common/resource.h"

#include <memory>

namespace BattleRoom {

class ServerClient : public Resource {

public:

}; // ServerClient class


typedef std::unique_ptr<ServerClient> UniqueServerClient;

} // BattleRoom namespace
#endif // SERVER_CLIENT_H

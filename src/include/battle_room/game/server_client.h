#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include "battle_room/common/resource.h"
#include "battle_room/game/game_object.h"

#include <memory>
#include <vector>

namespace BattleRoom {

class ServerClient : public Resource {

public:

    virtual std::vector<GameObject> getAllGameObjects() = 0;

}; // ServerClient class


typedef std::unique_ptr<ServerClient> UniqueServerClient;

} // BattleRoom namespace
#endif // SERVER_CLIENT_H

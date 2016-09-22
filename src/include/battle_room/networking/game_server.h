#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include "battle_room/common/resource.h"

#include <thread>

namespace BattleRoom {

class GameServer : public Resource {

public:

    // constructor
    GameServer(ResourceDescriptor settings);
    ~GameServer();

    // inherited
    void applySettings(ResourceDescriptor settings);

private:

    std::thread m_serverThread; ///< Thread to update world on
    bool m_keepGoing; ///< Set to false when ready to destroy

}; // GameServer class
} // BattleRoom namespace
#endif // GAME_SERVER_H

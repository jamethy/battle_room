#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include "interfaces/gamedata_interface.h"
#include "handlers/players.h"

namespace GameInterface
{


class GameHandler : public GameDataClass
{
public:
    GameHandler();
    ~GameHandler();

    void update();

    PlayerControl* getHumanPlayer();
    std::vector<PlayerControl*> getNetworkPlayers();
    std::vector<PlayerControl*> getAIPlayers();

private:

    PlayerHandler m_players;
};

} // GameInterface namespace
#endif // GAMEHANDLER_H

#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include "interfaces/gamedata_interface.h"
#include "gamedata/handlers/players.h"
#include "gamedata/handlers/world.h"

namespace GameInterface
{


class GameHandler : public GameDataClass
{
public:


    GameHandler();
    ~GameHandler();

    void update();
    void updateGraphics();

    PlayerControl* getHumanPlayer();
    std::vector<PlayerControl*> getNetworkPlayers();
    std::vector<PlayerControl*> getAIPlayers();


    void startTestWorld();

private:

    PlayerHandler m_players;
    WorldHandler m_world;
};

} // GameInterface namespace
#endif // GAMEHANDLER_H

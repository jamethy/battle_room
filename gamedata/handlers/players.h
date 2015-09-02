#ifndef PLAYERS_HANDLER_H
#define PLAYERS_HANDLER_H

#include "../objects/player.h"

#include <vector>

namespace GameInterface
{

class PlayerHandler
{
public:
    PlayerHandler();
    ~PlayerHandler();

    BasePlayerObject *addPlayer();
    void removePlayer(BasePlayerObject *player);

    std::vector<UniquePlayer>::iterator begin();
    std::vector<UniquePlayer>::iterator end();

private:

    std::vector<UniquePlayer> m_objects;
};

} // GameInterface namespace
#endif // PLAYERS_HANDLER_H

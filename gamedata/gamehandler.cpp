
#include "gamehandler.h"


namespace GameInterface {



UniqueGameData createGameData()
{
    return UniqueGameData(new GameHandler());
}




GameHandler::GameHandler()
{

}

GameHandler::~GameHandler()
{

}

void GameHandler::update()
{

}

PlayerControl* GameHandler::getHumanPlayer()
{
    for(UniquePlayer& p : m_players)
    {
        UserInput* pc = p.get()->getControl();
        if(pc->getController() == Human) return pc;
    }
    return nullptr;
}

std::vector<PlayerControl*> GameHandler::getNetworkPlayers()
{
    std::vector<PlayerControl*> retvec;
    for(UniquePlayer& p : m_players)
    {
        UserInput* pc = p.get()->getControl();
        if(pc->getController() == Network) retvec.push_back(pc);
    }
    return retvec;
}

std::vector<PlayerControl*> GameHandler::getAIPlayers()
{
    std::vector<PlayerControl*> retvec;
    for(UniquePlayer& p : m_players)
    {
        UserInput* pc = p.get()->getControl();
        if(pc->getController() == AI) retvec.push_back(pc);
    }
    return retvec;
}

} // GameInterface namespace

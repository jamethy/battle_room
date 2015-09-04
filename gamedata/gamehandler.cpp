
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

void GameHandler::update(const double& gameTime)
{
    static double last_time = 0;
    double delta_time = gameTime - last_time;
    for(UniquePlayer& p : m_players) p->update(delta_time);
}

void GameHandler::updateGraphics()
{
    for(UniquePlayer& p : m_players) p->updateGraphics();
    for(UniqueWorldObject& p : m_world) p->updateGraphics();
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



void GameHandler::startTestWorld()
{
    m_players.clear();
    m_world.clear();

    m_players.addPlayer()->getControl()->changeControlTo(Human);
    m_players.addPlayer()->moveTo(Utility::WorldPos(1,-3));
    m_players.addPlayer()->moveTo(Utility::WorldPos(2,3));

    m_world.addObject(GraphicsInterface::Star)->moveTo(Utility::WorldPos(2.5,3));
    m_world.addObject(GraphicsInterface::Star)->moveTo(Utility::WorldPos(-2.5,3));
    m_world.addObject(GraphicsInterface::Star)->moveTo(Utility::WorldPos(0,2));
}



} // GameInterface namespace

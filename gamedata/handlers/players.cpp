#include "players.h"

namespace GameInterface
{

PlayerHandler::PlayerHandler()
{

}

PlayerHandler::~PlayerHandler()
{

}

BasePlayerObject *PlayerHandler::addPlayer()
{
    m_objects.push_back(UniquePlayer(new ConcretePlayerObject()));
    return m_objects.back().get();
}

void PlayerHandler::removePlayer(BasePlayerObject *player)
{
    std::vector<UniquePlayer>::reverse_iterator rd;
    for (rd = m_objects.rbegin(); rd != m_objects.rend(); std::advance(rd,1))
    {
        if ((*rd).get() == player)
        {
            std::advance(rd,1);
            m_objects.erase(rd.base());
            return;
        }
    }
}

std::vector<UniquePlayer>::iterator PlayerHandler::begin()
    { return m_objects.begin(); }
std::vector<UniquePlayer>::iterator PlayerHandler::end()
    { return m_objects.end(); }







} // GameInterface namespace


#include "playercontrol.h"

namespace GameInterface
{

UserInput::UserInput()
{

}

UserInput::~UserInput()
{

}

void UserInput::addInput(PlayerInputInterface::PlayerInputClass *input)
{
    m_inputqueue.push_back(input);
}

void UserInput::changeControlTo(Controller who)
{
    m_controller = who;
}

Controller UserInput::getController()
{
    return m_controller;
}


} // GameInterface namespace

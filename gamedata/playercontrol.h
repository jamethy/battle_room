#ifndef PLAYERCONTROL_H
#define PLAYERCONTROL_H

#include "interfaces/gamedata_interface.h"

namespace GameInterface
{


enum Controller
{
    Human,
    Network,
    AI
};

class UserInput : public PlayerControl
{
public:
    UserInput();
    ~UserInput();
    void addInput(PlayerInputInterface::PlayerInputClass* input);

    void changeControlTo(Controller who);
    Controller getController();

private:

    std::vector<PlayerInputInterface::PlayerInputClass*> m_inputqueue;
    Controller m_controller = AI;
};


} // GameInterface namespace
#endif // PLAYERCONTROL_H

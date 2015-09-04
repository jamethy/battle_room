#ifndef GAMEDATA_INTERFACE_H
#define GAMEDATA_INTERFACE_H

#include "playerinput_interface.h"

#include <memory>
#include <vector>

namespace GameInterface
{



class PlayerControl
{
public:
    virtual ~PlayerControl(){}
    virtual void addInput(PlayerInputInterface::PlayerInputClass* input) = 0;

};


class GameDataClass
{
public:

    virtual void startTestWorld() = 0;

    virtual void update(const double& gameTime) = 0;
    virtual void updateGraphics() = 0;
    virtual ~GameDataClass(){}

    virtual PlayerControl* getHumanPlayer() = 0;
    virtual std::vector<PlayerControl*> getNetworkPlayers() = 0;
    virtual std::vector<PlayerControl*> getAIPlayers() = 0;
};

typedef std::unique_ptr<GameDataClass> UniqueGameData;
UniqueGameData createGameData();


}

#endif

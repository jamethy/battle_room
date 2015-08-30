#ifndef GAMEDATA_INTERFACE_H
#define GAMEDATA_INTERFACE_H

#include <memory>

namespace GameInterface
{

class GameDataClass
{
public:
    virtual void update() = 0;
    virtual ~GameDataClass(){}
};

typedef std::unique_ptr<GameDataClass> UniqueGameData;
UniqueGameData createGameData();

}

#endif

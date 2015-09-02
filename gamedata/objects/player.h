#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "baseplayer.h"

class PlayerHandler;

namespace GameInterface
{

class ConcretePlayerObject : public BasePlayerObject
{
    friend class PlayerHandler;

protected:
    ConcretePlayerObject();
    ~ConcretePlayerObject();

};

} // GameInterface namespace
#endif // PLAYER_OBJECT_H

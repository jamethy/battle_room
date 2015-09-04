#ifndef BASEPLAYER_H
#define BASEPLAYER_H

#include "interfaces/gamedata_interface.h"
#include "gamedata/playercontrol.h"
#include "baseobject.h"

namespace GameInterface
{



class BasePlayerObject : public ObjectBaseClass
{
public:
    BasePlayerObject(GraphicsInterface::ObjectType type);
    virtual ~BasePlayerObject();

    virtual void update(const double& timestep);
    UserInput* getControl(){ return &m_playerControl; }


private:

    UserInput m_playerControl;
};

typedef std::unique_ptr<BasePlayerObject> UniquePlayer;

}// GameInterface namespace
#endif // BASEPLAYER_H

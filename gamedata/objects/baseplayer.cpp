#include "baseplayer.h"

namespace GameInterface
{

BasePlayerObject::BasePlayerObject(GraphicsInterface::ObjectType type)
    : ObjectBaseClass(type)
{

}

BasePlayerObject::~BasePlayerObject()
{

}

void BasePlayerObject::update(const double &timestep)
{
}



} // GameInterface namespace

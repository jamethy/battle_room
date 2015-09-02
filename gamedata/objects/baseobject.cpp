
#include "baseobject.h"

namespace GameInterface
{


ObjectBaseClass::ObjectBaseClass(GraphicsInterface::ObjectType type)
    : m_graphics(GraphicsInterface::createObject(type))
{
}

ObjectBaseClass::~ObjectBaseClass()
{
}


} // GameInterface namespace

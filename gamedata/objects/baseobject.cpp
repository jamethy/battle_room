
#include "baseobject.h"

namespace GameInterface
{


ObjectBaseClass::ObjectBaseClass(GraphicsInterface::ObjectType type)
    : m_graphics(GraphicsInterface::createObject(type))
{
}

void ObjectBaseClass::updateGraphics()
{
    m_graphics.get()->setPos(m_centroid,m_theta);
}

ObjectBaseClass::~ObjectBaseClass()
{
}

void ObjectBaseClass::moveTo(const Utility::WorldPos &position)
{
    m_centroid = position;
}

void ObjectBaseClass::rotateTo(const double &theta)
{
    m_theta = theta;
}


} // GameInterface namespace

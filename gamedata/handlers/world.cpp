#include "world.h"

namespace GameInterface
{

WorldHandler::WorldHandler()
{

}

WorldHandler::~WorldHandler()
{

}

BaseWorldObject *WorldHandler::addObject(GraphicsInterface::ObjectType type)
{
    switch (type) {
    case GraphicsInterface::Star:
        m_objects.push_back(UniqueWorldObject(new StarObject()));
        break;
    default:
        return nullptr;
        break;
    }
    return m_objects.back().get();
}

void WorldHandler::removeObject(BaseWorldObject *object)
{
    std::vector<UniqueWorldObject>::reverse_iterator rd;
    for (rd = m_objects.rbegin(); rd != m_objects.rend(); std::advance(rd,1))
    {
        if ((*rd).get() == object)
        {
            std::advance(rd,1);
            m_objects.erase(rd.base());
            return;
        }
    }
}

std::vector<UniqueWorldObject>::iterator WorldHandler::begin()
    { return m_objects.begin(); }
std::vector<UniqueWorldObject>::iterator WorldHandler::end()
    { return m_objects.end(); }
void WorldHandler::clear()
    { return m_objects.clear(); }



} // GameInterface namespace

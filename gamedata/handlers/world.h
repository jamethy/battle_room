#ifndef WORLD_HANDLER_H
#define WORLD_HANDLER_H

#include "../objects/star.h"

#include <vector>

namespace GameInterface
{

class WorldHandler
{
public:
    WorldHandler();
    ~WorldHandler();

    BaseWorldObject *addObject(GraphicsInterface::ObjectType type);
    void removeObject(BaseWorldObject* object);

    std::vector<UniqueWorldObject>::iterator begin();
    std::vector<UniqueWorldObject>::iterator end();
    void clear();

private:

    std::vector<UniqueWorldObject> m_objects;
};

} // GameInterface namespace
#endif // WORLD_HANDLER_H

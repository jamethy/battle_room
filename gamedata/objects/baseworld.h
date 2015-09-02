#ifndef BASEWORLD_H
#define BASEWORLD_H

#include "baseobject.h"

namespace GameInterface
{

class BaseWorldObject : public ObjectBaseClass
{
public:
    BaseWorldObject(GraphicsInterface::ObjectType type);
    virtual ~BaseWorldObject();
};

typedef std::unique_ptr<BaseWorldObject> UniqueWorldObject;

}// GameInterface namespace
#endif // BASEWORLD_H

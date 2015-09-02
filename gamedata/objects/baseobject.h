#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "interfaces/graphics_interface.h"

#include <memory>

namespace GameInterface
{

class ObjectBaseClass
{
public:


    virtual ~ObjectBaseClass();

protected:
    ObjectBaseClass(GraphicsInterface::ObjectType type);

private:

    GraphicsInterface::UniqueDrawableObject m_graphics;
};

} // GameInterface namespace
#endif // OBJECTBASE_H

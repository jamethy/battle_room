#ifndef OBJECT_HANDLER_H
#define OBJECT_HANDLER_H

#include "../interfaces/graphics_interface.h"

#include <vector>
#include <memory>

namespace GraphicsInterface
{

typedef std::vector< DrawableObjectClass* >::iterator ObjIt;


class ObjectHandlerClass
{

public:

    static ObjectHandlerClass* Instance();

    void removeObject(DrawableObjectClass* obj);
    void addObject(DrawableObjectClass* obj);

    ObjIt begin();
    ObjIt end();
    unsigned int size();

private:
    ObjectHandlerClass();
    ~ObjectHandlerClass();

    static ObjectHandlerClass* m_ptr;

    std::vector< DrawableObjectClass* > m_objects;
};


} // end GraphicsInterface
#endif // OBJECT_HANDLER_H

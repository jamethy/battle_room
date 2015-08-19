#ifndef OBJECT_HANDLER_H
#define OBJECT_HANDLER_H

#include "../interfaces/graphics_interface.h"

#include <vector>
#include <memory>

namespace GraphicsInterface
{

class ObjectHandlerClass
{
private:
    ObjectHandlerClass();
    ~ObjectHandlerClass();

    static ObjectHandlerClass* m_ptr;

    std::vector< DrawableObjectClass* > m_objects;

public:

    static ObjectHandlerClass* Instance();

    void removeObject(DrawableObjectClass* obj);
    void addObject(DrawableObjectClass* obj);

};


} // end GraphicsInterface
#endif // OBJECT_HANDLER_H

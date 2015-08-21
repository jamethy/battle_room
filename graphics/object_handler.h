#ifndef OBJECT_HANDLER_H
#define OBJECT_HANDLER_H

#include "../interfaces/graphics_interface.h"

#include <vector>

namespace GraphicsInterface
{

typedef std::vector< DrawableObjectClass* >::iterator ObjIt;



class ObjectVectorClass
{

public:

    ObjIt begin();
    ObjIt end();
    unsigned int size();

    ObjectVectorClass();
    virtual ~ObjectVectorClass();

protected:
    std::vector< DrawableObjectClass* > m_objects;
    void removeObject(DrawableObjectClass* obj);
};





class ObjectHandlerClass : public ObjectVectorClass
{

public:

    static ObjectHandlerClass* Instance();

    void update();

    void addObjectToAddQueue(DrawableObjectClass* obj);
    void addObjectToRemoveQueue(DrawableObjectClass* obj);
    ~ObjectHandlerClass();

private:
    ObjectHandlerClass();

    static ObjectHandlerClass* m_ptr;

    std::vector< DrawableObjectClass* > m_object_addqueue;
    std::vector< DrawableObjectClass* > m_object_removequeue;
};


} // end GraphicsInterface
#endif // OBJECT_HANDLER_H

#ifndef OBJECT_HANDLER_H
#define OBJECT_HANDLER_H

#include "../interfaces/graphics_interface.h"
#include "../graphics/graphics_layer.h"

#include <vector>

namespace GraphicsInterface
{

typedef std::vector< GraphicsLayer* >::iterator ObjIt;



class ObjectVectorClass
{

public:

    ObjIt begin();
    ObjIt end();
    unsigned int size();

    ObjectVectorClass();
    virtual ~ObjectVectorClass();

protected:
    std::vector< GraphicsLayer* > m_objects;
    void removeObject(GraphicsLayer* obj);
};





class ObjectHandlerClass : public ObjectVectorClass
{

public:

    static ObjectHandlerClass* Instance();

    void update();

    void addObjectToAddQueue(GraphicsLayer* obj);
    void addObjectToRemoveQueue(GraphicsLayer* obj);
    ~ObjectHandlerClass();

private:
    ObjectHandlerClass();

    static ObjectHandlerClass* m_ptr;

    std::vector< GraphicsLayer* > m_object_addqueue;
    std::vector< GraphicsLayer* > m_object_removequeue;
};


} // end GraphicsInterface
#endif // OBJECT_HANDLER_H

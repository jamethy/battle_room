#include "object_handler.h"
#include "player_object.h"
#include "star_object.h"

namespace GraphicsInterface
{

////// DrawabledObjectClass //////////////////////////////////////////////////////////////////////
////// DrawabledObjectClass //////////////////////////////////////////////////////////////////////
////// DrawabledObjectClass //////////////////////////////////////////////////////////////////////

DrawableObjectClass::~DrawableObjectClass()
{
    GraphicsLayer* gl = dynamic_cast<GraphicsLayer*>(this);
    ObjectHandlerClass::Instance()->addObjectToRemoveQueue(gl);
}


////// Global Functions //////////////////////////////////////////////////////////////////////
////// Global Functions //////////////////////////////////////////////////////////////////////
////// Global Functions //////////////////////////////////////////////////////////////////////

UniqueDrawableObject createObject(ObjectType obj)
{
    UniqueDrawableObject retobj;

    switch (obj)
    {

    case Player:
        retobj = UniqueDrawableObject(new PlayerObject());
        break;
    case Star:
        retobj = UniqueDrawableObject(new StarObject());
        break;
    default:
        return nullptr;
        break;

    }

    ObjectHandlerClass::Instance()->addObjectToAddQueue((GraphicsLayer*)retobj.get());
    return retobj;
}



////// ObjectVectorClass //////////////////////////////////////////////////////////////////////
////// ObjectVectorClass //////////////////////////////////////////////////////////////////////
////// ObjectVectorClass //////////////////////////////////////////////////////////////////////

ObjectVectorClass::ObjectVectorClass() { }
ObjectVectorClass::~ObjectVectorClass() { }


ObjIt ObjectVectorClass::begin() { return m_objects.begin(); }
ObjIt ObjectVectorClass::end() { return m_objects.end(); }
unsigned int ObjectVectorClass::size() { return m_objects.size(); }

void ObjectVectorClass::removeObject(GraphicsLayer *obj)
{
    std::vector<GraphicsLayer*>::reverse_iterator rd;
    for (rd = m_objects.rbegin(); rd != m_objects.rend(); std::advance(rd,1))
    {
        if (*rd == obj)
        {
            std::advance(rd,1);
            m_objects.erase(rd.base());
            return;
        }
    }}





////// ObjectHandlerClass //////////////////////////////////////////////////////////////////////
////// ObjectHandlerClass //////////////////////////////////////////////////////////////////////
////// ObjectHandlerClass //////////////////////////////////////////////////////////////////////

ObjectHandlerClass* ObjectHandlerClass::m_ptr = nullptr;

ObjectHandlerClass::ObjectHandlerClass() { }
ObjectHandlerClass::~ObjectHandlerClass() { }



ObjectHandlerClass* ObjectHandlerClass::Instance()
{
    if (m_ptr == nullptr) m_ptr = new ObjectHandlerClass();
    return m_ptr;
}

void ObjectHandlerClass::update()
{
    for(GraphicsLayer* addobj : m_object_addqueue) m_objects.push_back(addobj);
    m_object_addqueue.clear();

    for(GraphicsLayer* remobj : m_object_removequeue) removeObject(remobj);
    m_object_removequeue.clear();

    for(GraphicsLayer* obj : m_objects) obj->update();
}


void ObjectHandlerClass::addObjectToAddQueue(GraphicsLayer *obj)
{
    if (obj == nullptr) return;
    m_object_addqueue.push_back(obj);
}


void ObjectHandlerClass::addObjectToRemoveQueue(GraphicsLayer *obj)
{
    if (obj == nullptr) return;
    m_object_removequeue.push_back(obj);
}


} // end GraphicsInterface

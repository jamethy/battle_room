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
    ObjectHandlerClass::Instance()->addObjectToRemoveQueue(this);
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

    ObjectHandlerClass::Instance()->addObjectToAddQueue(retobj.get());
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

void ObjectVectorClass::removeObject(DrawableObjectClass *obj)
{
    std::vector<DrawableObjectClass*>::reverse_iterator rd;
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
    for(DrawableObjectClass* addobj : m_object_addqueue) m_objects.push_back(addobj);
    m_object_addqueue.clear();

    for(DrawableObjectClass* remobj : m_object_removequeue) removeObject(remobj);
    m_object_removequeue.clear();
}


void ObjectHandlerClass::addObjectToAddQueue(DrawableObjectClass *obj)
{
    if (obj == nullptr) return;
    m_object_addqueue.push_back(obj);
}


void ObjectHandlerClass::addObjectToRemoveQueue(DrawableObjectClass *obj)
{
    if (obj == nullptr) return;
    m_object_removequeue.push_back(obj);
}


} // end GraphicsInterface

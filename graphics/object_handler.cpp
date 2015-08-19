#include "object_handler.h"
#include "player_object.h"
#include "star_object.h"

namespace GraphicsInterface
{

ObjectHandlerClass* ObjectHandlerClass::m_ptr = nullptr;

DrawableObjectClass::~DrawableObjectClass()
{
    ObjectHandlerClass::Instance()->removeObject(this);
}


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

    ObjectHandlerClass::Instance()->addObject(retobj.get());
    return retobj;
}




ObjectHandlerClass::ObjectHandlerClass()
{

}

ObjectHandlerClass::~ObjectHandlerClass()
{
    for (DrawableObjectClass* d : m_objects) delete d;
}


ObjectHandlerClass* ObjectHandlerClass::Instance()
{
    if (m_ptr == nullptr) m_ptr = new ObjectHandlerClass();
    return m_ptr;
}

void ObjectHandlerClass::removeObject(DrawableObjectClass* obj)
{
    if (obj == nullptr) return;

    std::vector<DrawableObjectClass*>::reverse_iterator rd;
    for (rd = m_objects.rbegin(); rd != m_objects.rend(); std::advance(rd,1))
    {
        if (*rd == obj)
        {
            std::advance(rd,1);
            m_objects.erase(rd.base());
            return;
        }
    }
}


void ObjectHandlerClass::addObject(DrawableObjectClass *obj)
{
    if (obj == nullptr) return;
    m_objects.push_back(obj);
}


} // end GraphicsInterface

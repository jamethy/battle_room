#include "interfaces/graphics_interface.h"
#include "graphics/object_handler.h"
#include "graphics/graphics_layer.h"
#include "graphics/player_object.h"
#include "graphics/star_object.h"

#include "utility/br_vectors.h"

#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>
#include <thread>

using namespace std;
using namespace GraphicsInterface;

typedef pair<ObjectType,string> objpair;
vector<objpair> objs;

void check_test(bool result, std::string name)
{
    if(result) std::cout << "Success: " << name << ".\n";
    else std::cerr << "Failure: " << name << ".\n";
}




void createObjectTest(objpair& op)
{
    UniqueDrawableObject p1 = createObject(op.first);
    if(p1 != nullptr) check_test( op.second.compare(typeid(*p1).name())==0, "createObject " + op.second);
    else check_test(false, "createObjectTest " + op.second);
}





void moveObjectTest(objpair& op)
{
    UniqueDrawableObject obj = createObject(op.first);
    Utility::vec2d pos(1,2);
    double th = 3;

    obj->setPos(pos,th);
    GraphicsLayer* gl = dynamic_cast<GraphicsLayer*>( obj.get() );

    if(gl != nullptr)
    {
        bool result = gl->getPos() == pos && gl->getTh() == th;
        check_test(result, "moveObjectTest " + op.second);
    }
    else
    {
        std::cerr << "Failed to convert " << op.second << " into GraphicsLayer.\n";
    }

}


void objectHandlerSizeTest(objpair& op)
{
    bool result = true;
    ObjectHandlerClass* ohc = ObjectHandlerClass::Instance();
    unsigned int start_size = ohc->size();

    // creating objects
    UniqueDrawableObject obj1 = createObject(op.first); ohc->update();
    result = result && ohc->size() == start_size + 1;
    UniqueDrawableObject obj2 = createObject(op.first); ohc->update();
    result = result && ohc->size() == start_size + 2;
    UniqueDrawableObject obj3 = createObject(op.first); ohc->update();
    result = result && ohc->size() == start_size + 3;

    // looping over objects
    unsigned int count = 0;
    for(DrawableObjectClass* doc : *ohc) count += 1;
    result = result && count == start_size + 3;

    // deleting objects
    delete obj1.release(); ohc->update();
    result = result && ohc->size() == start_size + 2;
    delete obj2.release(); ohc->update();
    result = result && ohc->size() == start_size + 1;
    delete obj3.release(); ohc->update();
    result = result && ohc->size() == start_size;

    check_test(result, "objectHandlerSizeTest " + op.second);
}



void createWindowTest()
{
    UniqueGraphicsWindow w = createWindow(500,500);
    check_test( w.get() != nullptr, "createWindowTest 500 500");
}


void drawObjects(objpair& op)
{
    bool result = false;
    UniqueGraphicsWindow w = createWindow(500,500);
    if (w.get() != nullptr)
    {
        UniqueDrawableObject obj1 = createObject(op.first);
        UniqueDrawableObject obj2 = createObject(op.first);
        UniqueDrawableObject obj3 = createObject(op.first);

        for(unsigned i = 0; i < 100; ++i)
        {
            w->update();
        }
    }

    check_test( result, "drawObjects " + op.second);
}


int main()
{
    objs.push_back(make_pair( Player, typeid(PlayerObject).name() ));
    objs.push_back(make_pair( Star, typeid(StarObject).name() ));

    for(objpair& op : objs) createObjectTest(op);
    for(objpair& op : objs) moveObjectTest(op);
    for(objpair& op : objs) objectHandlerSizeTest(op);

    createWindowTest();
    for(objpair& op : objs) drawObjects(op);

    return 0;
}

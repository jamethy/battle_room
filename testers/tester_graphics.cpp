#include "interfaces/graphics_interface.h"
#include "graphics/object_handler.h"
#include "graphics/graphics_layer.h"
#include "graphics/camera.h"

#include "utility/br_vectors.h"

#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>
#include <thread>

using namespace std;
using namespace GraphicsInterface;
using namespace Utility;

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
    GraphicsLayer* gl = (GraphicsLayer*)p1.get();
    if(p1 != nullptr) check_test( op.first == gl->getType(), "createObject " + op.second);
    else check_test(false, "createObjectTest " + op.second);
}





void moveObjectTest(objpair& op)
{
    UniqueDrawableObject obj = createObject(op.first);
    Utility::vec2d pos(1,2);
    double th = 3;

    obj->setPos(pos,th);
    GraphicsLayer* gl = (GraphicsLayer*)obj.get();

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
    Utility::vec2d pos(0,0);
    bool result = true;
    UniqueGraphicsWindow w = createWindow(500,500);
    if (w.get() == nullptr) result = false;
    else
    {
        UniqueDrawableObject obj1 = createObject(op.first); obj1->setPos(pos,0);
        UniqueDrawableObject obj2 = createObject(op.first); obj2->setPos(pos,0);
        UniqueDrawableObject obj3 = createObject(op.first); obj3->setPos(pos,0);

        for(unsigned i = 0; i < 60; ++i)
        {
            std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
            w->update();
            std::this_thread::sleep_until(t1+std::chrono::milliseconds(17));
        }
    }

    check_test( result, "drawObjects " + op.second);
}

void setCameraPosition()
{
    bool result = true;
    CameraClass cam(500,500);
    cam.setCameraBounds(WorldPos(-5000,-50000),WorldPos(50000,50000));

    CameraPos campos(WorldPos(1,2),3,4);

    cam.setCameraPosition(campos);
    CameraPos newpos = cam.getCameraPosition();

    result = result && newpos.pos == WorldPos(1,2);
    result = result && newpos.th == 3;
    result = result && newpos.z == 4;

    check_test( result, "setCameraPosition");
}

void moveCamera()
{
    bool result = true;
    CameraClass cam(500,500);
    cam.setCameraBounds(WorldPos(-5000,-50000),WorldPos(50000,50000));

    CameraPos campos(WorldPos(0,0),0,0);
    cam.setCameraPosition(campos);
    cam.moveInX(2); cam.moveInY(3); cam.moveInZ(4); cam.rotate(1);
    CameraPos newpos = cam.getCameraPosition();

    result = result && newpos.pos == WorldPos(2,3);
    result = result && newpos.z == 4;
    result = result && newpos.th == 1;

    check_test( result, "moveCamera");
}


void moveCameraOutOfBounds()
{
    bool result = true;
    CameraClass cam(500,500);
    cam.setCameraBounds(WorldPos(-50,-50),WorldPos(50,50));
    typedef std::pair<CameraPos,CameraPos> campair; // position and if in bounds

    std::vector<campair> cam_positions;
    cam_positions.push_back(campair(CameraPos(WorldPos(0,0),0,0),    CameraPos(WorldPos(0,0),0,0)));
    cam_positions.push_back(campair(CameraPos(WorldPos(10000,0),0,0),CameraPos(WorldPos(10000,0),0,0)));

    for(campair& p : cam_positions)
    {
        cam.setCameraPosition(p.first);
        cam.update();
        result = result && (p.second == cam.getCameraPosition());
    }

    check_test( result, "moveCameraOutOfBounds");

}





int main()
{
    objs.push_back(make_pair( Player, "Player" ));
    objs.push_back(make_pair( Star, "Star" ));
    objs.push_back(make_pair( Wall, "Wall" ));

    for(objpair& op : objs) createObjectTest(op);
    for(objpair& op : objs) moveObjectTest(op);
    for(objpair& op : objs) objectHandlerSizeTest(op);

    createWindowTest();
    for(objpair& op : objs) drawObjects(op);

    moveCamera();
    moveCameraOutOfBounds();

    return 0;
}

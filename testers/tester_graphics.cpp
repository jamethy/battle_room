#include "interfaces/graphics_interface.h"
#include "graphics/player_object.h"
#include "graphics/star_object.h"
#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>

using namespace std;
using namespace GraphicsInterface;

void check_test(bool result, std::string name)
{
    if(result) std::cout << "Success: " << name << ".\n";
    else std::cerr << "Failure: " << name << ".\n";
}


void createObjectTest()
{
    typedef pair<ObjectType,string> objpair;

    vector<objpair> objs;
    objs.push_back(make_pair( Player, typeid(PlayerObject).name() ));
    objs.push_back(make_pair( Star, typeid(StarObject).name() ));

    for (objpair& op : objs)
    {
        UniqueDrawableObject p1 = createObject(op.first);
        if(p1 != nullptr) check_test( op.second.compare(typeid(*p1).name())==0, "createObject " + op.second);
        else check_test(false, "createObject " + op.second);
    }
}


int main()
{
    createObjectTest();

    return 0;
}

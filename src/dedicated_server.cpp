#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/input_gatherer.h"

#include "battle_room/common/animation_handler.h"

#include <iostream>
#include <thread>

using namespace BattleRoom;

int main() {

    std::cout << "Hello World!\n";
    std::string resourcePath = "../res"; //TODO do get resource path correctly
    AnimationHandler::setResourcePath(resourcePath + "/animations/");

    std::string settings_file = resourcePath + "/dedicated_startup" + DESCRIPTOR_EXTENSION;
    ResourceDescriptor rd = ResourceDescriptor::readFile(settings_file);

    
    return 0;

} // end main

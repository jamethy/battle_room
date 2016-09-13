#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/file_utils.h"
#include "battle_room/common/string_utils.h"

#include <iostream>
#include <thread>

using namespace BattleRoom;

int main(int argc, char** argv) {

    setResourcePathFromExe(argv[0]);

    std::string settings_file = getResourcePath() + "/dedicated_startup" + DESCRIPTOR_EXTENSION;
    ResourceDescriptor rd = ResourceDescriptor::readFile(settings_file);

    if (isNotEmpty(rd.getKey())) {
        std::cout << "Starting server from resource " << settings_file << std::endl;
    }
    
    return 0;

} // end main

#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/file_utils.h"
#include "battle_room/common/string_utils.h"

#include "battle_room/game/query_world.h"

#include "battle_room/networking/game_server.h"
#include "battle_room/networking/world_updater_factory.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace BattleRoom;

int main(int argc, char** argv) {

    setResourcePathFromExe(argv[0]);

    std::string settings_file = getResourcePath() + "/dedicated_startup" + DESCRIPTOR_EXTENSION;
    ResourceDescriptor rd = ResourceDescriptor::readFile(settings_file);

    if (isNotEmpty(rd.getKey())) {
        std::cout << "Starting server from resource " << settings_file << std::endl;
    }

    UniqueWorldUpdater worldUpdater = WorldUpdaterFactory::createWorldUpdater(
            rd.getSubResource("WorldUpdater")
    );

    GameServer(rd.getSubResource("Server"));

    while(true) { // temp

        QueryWorld::updateBuffer();

        // need to sleep or something or else this will jam up the mutex
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    return 0;

} // end main

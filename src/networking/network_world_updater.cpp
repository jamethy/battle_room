#include "battle_room/networking/network_world_updater.h"
#include "battle_room/game/query_world.h"
#include "battle_room/game/command_receiver.h"

#include <chrono>

namespace BattleRoom {

// apply settings
void NetworkWorldUpdater::applySettings(ResourceDescriptor settings) {

    // apply network settings
        // ip address
        // port
}

void worldUpdaterFunction(World& world, bool& keepUpdating) {

    while(keepUpdating) {

        std::vector<Command> commands = CommandReceiver::getAndClearCommands();
        // send commands to server

        // request world updates?
        // receive udp messages?

        // fake load
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        QueryWorld::updateCopyWorld(world);
    }
}

// constructors
NetworkWorldUpdater::NetworkWorldUpdater(ResourceDescriptor settings) 
    : m_keepUpdating(true)
{
    applySettings(settings);

    m_worldThread = std::thread(worldUpdaterFunction,
            std::ref(m_world),
            std::ref(m_keepUpdating)
    );
}

NetworkWorldUpdater::~NetworkWorldUpdater() {
    m_keepUpdating = false; //TODO make this an atomic boolean
    if (m_worldThread.joinable()) {
        m_worldThread.join();
    }

    // close network connections?
}

} // BattleRoom namespace

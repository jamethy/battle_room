#include "battle_room/networking/server_connection.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace BattleRoom;

int main(int argc, char **argv) {
    (void) argc; // unused
    (void) argv; 


    UniqueServerConnection server = createServerConnection();
    server->start(8080);

    while (true) { // temp

        // need to sleep or something or else this will jam up the mutex
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;

} // end main

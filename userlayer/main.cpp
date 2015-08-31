#include "interfaces/graphics_interface.h"
#include "interfaces/gamedata_interface.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;

 duration<double> ng_time;
unsigned ng_count = 0;


void updateGame(GameInterface::GameDataClass* gd){ gd->update(); }

void updateNongraphics(
        GameInterface::GameDataClass* gd
        //...
        )
{
    steady_clock::time_point start = steady_clock::now();
    std::thread game(updateGame,gd);
    // maybe process some input
    // maybe some other stuff
    game.join();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    steady_clock::time_point stop = steady_clock::now();
    ng_time += duration_cast< duration<double> > (stop-start);
    ++ng_count;
}

int main()
{
    GraphicsInterface::UniqueGraphicsWindow w = GraphicsInterface::createWindow(500,500);
    GameInterface::UniqueGameData gd = GameInterface::createGameData();

    duration<double> g_time;
    unsigned g_count = 0;

    for(unsigned i = 0; i < 120; ++i){

        steady_clock::time_point start = steady_clock::now(); // temporary max fps of 60

        std::thread nongraphics(updateNongraphics,gd.get());
        w->update();
        nongraphics.join();
        steady_clock::time_point stop = steady_clock::now();
        g_time += duration_cast< duration<double> > (stop-start);
        ++g_count;
        std::this_thread::sleep_until(start + std::chrono::milliseconds(17)); // temporary max fps of 60
    }

    std::cout << ng_time.count()/ng_count << std::endl;
    std::cout << g_time.count()/g_count << std::endl;

	return 0;
}

#include "interfaces/graphics_interface.h"
#include "interfaces/gamedata_interface.h"

#include <chrono>
#include <thread>

using std::chrono::steady_clock;

void updateGame(GameInterface::GameDataClass* gd){ gd->update(); }

void updateNongraphics(
        GameInterface::GameDataClass* gd
        //...
        )
{
    std::thread game(updateGame,gd);

    // maybe process some input
    // maybe some other stuff
    game.join();

}

int main()
{
    GraphicsInterface::UniqueGraphicsWindow w = GraphicsInterface::createWindow(1000,1000);
    GameInterface::UniqueGameData gd = GameInterface::createGameData();
    gd.get()->startTestWorld();

    for(unsigned i = 0; i < 120; ++i){

        steady_clock::time_point start = steady_clock::now(); // temporary max fps of 60

        std::thread nongraphics(updateNongraphics,gd.get());
        w->update();

        nongraphics.join();

        std::this_thread::sleep_until(start + std::chrono::milliseconds(17)); // temporary max fps of 60
    }


	return 0;
}

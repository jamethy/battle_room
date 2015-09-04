#include "interfaces/graphics_interface.h"
#include "interfaces/gamedata_interface.h"

#include "utility/br_time.h"

#include <chrono>
#include <thread>

using std::chrono::steady_clock;

void updateGame(const double& gameTime, GameInterface::GameDataClass* gd){ gd->update(gameTime); }

void updateNongraphics(
        const double& gameTime,
        GameInterface::GameDataClass* gd
        //...
        )
{
    std::thread game(updateGame, gameTime, gd);

    // maybe process some input
    // maybe some other stuff
    game.join();

}

int main()
{
    GraphicsInterface::UniqueGraphicsWindow w = GraphicsInterface::createWindow(1000,1000);
    GameInterface::UniqueGameData gd = GameInterface::createGameData();
    gd->startTestWorld();

    for(unsigned i = 0; i < 120; ++i){

        double gameTime = Utility::getTime();

        steady_clock::time_point start = steady_clock::now(); // temporary max fps of 60

        gd->updateGraphics();
        std::thread nongraphics(updateNongraphics, gameTime, gd.get());
        w->update(gameTime);

        nongraphics.join();

        std::this_thread::sleep_until(start + std::chrono::milliseconds(17)); // temporary max fps of 60
    }


	return 0;
}

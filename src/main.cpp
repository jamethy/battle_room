
#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/input_gatherer.h"
#include "battle_room/common/animation_handler.h"
#include "battle_room/common/file_utils.h"

#include "battle_room/game/query_world.h"

#include "battle_room/networking/world_updater_factory.h"

#include "battle_room/graphics/display_window.h"

#include "battle_room/user_interface/game_interface.h"

#include <iostream>
#include <thread>

using namespace BattleRoom;

int main(int argc, char** argv) {
    (void)argc; // unused

    setResourcePathFromExe(argv[0]);

    std::cout << "Hello World!\n";

    std::string settings_file = getResourcePath() + "/startup" + DESCRIPTOR_EXTENSION;
    ResourceDescriptor rd = ResourceDescriptor::readFile(settings_file);

    UniqueWorldUpdater worldUpdater = WorldUpdaterFactory::createWorldUpdater(
            rd.getSubResource("WorldUpdater")
    );

    std::vector<UniqueDisplayWindow> windows;
    for (ResourceDescriptor windowDescriptor : rd.getSubResources("Window")) {
        windows.push_back(createDisplayWindow(windowDescriptor));
    }

    std::vector<ViewInterface*> viewInterfaces; viewInterfaces.clear();
    std::vector<GameInterface> gameInterfaces; gameInterfaces.clear();

    for (ResourceDescriptor sub : rd.getSubResources("GameInterface")) {
        gameInterfaces.push_back(GameInterface(sub));
    }

    for (GameInterface& interface : gameInterfaces) {
        viewInterfaces.push_back(&interface);
    }

    while(!InputGatherer::containsQuitEvent()) { 

        // get inputs from last frame
        for (UniqueDisplayWindow& window : windows) {
            window->gatherInputs();
        }
        Inputs inputs = InputGatherer::getAndClearInputs();


        ///// start game interface thread
        std::thread interfaceThread( [&viewInterfaces, &windows, &inputs] () {

            // Handle inputs view interfaces
            for (ViewInterface* interface : viewInterfaces) {
                inputs = interface->handleInputs(inputs);
            }

            // Update world for client
            QueryWorld::updateBuffer();

            // Prepare objects for display
            for (ViewInterface* interface : viewInterfaces) {

                std::string associatedView = interface->getAssociatedView();
                std::vector<DrawableObject> objects = interface->getDrawableObjects();
                std::vector<DrawableText> texts = interface->getDrawableTexts();

                for (UniqueDisplayWindow& window : windows) {
                    window->addViewObjects( objects, associatedView );
                    window->addViewTexts( texts, associatedView );
                }
            }

            // Handle inputs for windows
            for (UniqueDisplayWindow& window : windows) {
                inputs = window->handleInputs(inputs);
            }

        });
        ////// End game interface thread


        ///// Start Drawing "thread" - must be on main thread
        for (UniqueDisplayWindow& window : windows) {
            window->drawScreen();
        }
        //// End drawing "thread"

        interfaceThread.join();

        // switch bufferes
        for (UniqueDisplayWindow& window : windows) {
            window->switchBuffers();
        }

    }
    
    return 0;

} // end main

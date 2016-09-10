
#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/input_gatherer.h"
#include "battle_room/common/animation_handler.h"

#include "battle_room/graphics/display_window.h"
#include "battle_room/graphics/get_resource_path.h"

#include "battle_room/game/game_interface.h"

#include <iostream>
#include <thread>

using namespace BattleRoom;

int main() {

    // Show Main menu
        // single player
            // Create local server < LocalWorld
            // Create menu overlay < gameinterface
            // get drawable objects
            // draw
            // get inputs
            // deal with inputs
            
        // multiplayer
            // Connect/Create network server < ClientWorld/ServerWorld
            // Create menu overlay < gameinterface
            // get drawable objects
            // draw
            // get inputs
            // deal with inputs
        // options
            // Menu navigation
        // exit


    // navigation commands
        // quit server / go to main menu
        // Create local server
        // Create local network server
        // Connect to network server

    // Server commands
        // pause request
        // all of player inputs
        // disconnect

    // player input path
        // Presses Key
        // Registered by SDL
        // After drawing frame, collected by InputManager
            // Views hit and zero plane intersection of them
            // Inputs contains view and mouse zero plane coordinates
        // Menus Look through Inputs and remove any used
            // if game commands, see bottom
            // if local commands, make changes
        // UI look through inputs and remove any used < gameinterface
            // This is mouse clicks on UI elements and commands
            // World does not use any inputs
            // if game commands, convert to commands and see bottom
            // if local commands, make changes
        // Command is sent to server
        // Commands are collected by server
        // Command is executed in server



    ///// Game States
    // dedicated server
    // Main menu
    // options over main menu
    // options over game
    // game client connected to server
    // game client as server
    // game client as single player
    // single player game paused






    std::cout << "Hello World!\n";
    std::string resourcePath = getResourcePath();
    AnimationHandler::setResourcePath(resourcePath + "/animations/");


    std::string settings_file = resourcePath + "/startup" + DESCRIPTOR_EXTENSION;
    ResourceDescriptor rd = ResourceDescriptor::readFile(settings_file);


    // --------------------------------------------------
    // GameState gameState;

    //Menus menus;
    // server
    //    GameWorld game;

    // Create main components of game
    //ProgramState state;

    GameWorld gameWorld(rd.getSubResource("GameWorld"));


    std::vector<UniqueDisplayWindow> windows;
    for (ResourceDescriptor windowDescriptor : rd.getSubResources("Window")) {
        windows.push_back(createDisplayWindow(windowDescriptor));
    }

    std::vector<ViewInterface*> viewInterfaces; viewInterfaces.clear();
    std::vector<GameInterface> gameInterfaces; gameInterfaces.clear();

    for (ResourceDescriptor sub : rd.getSubResources("GameInterface")) {
        gameInterfaces.push_back(GameInterface(gameWorld, sub));
        viewInterfaces.push_back(&gameInterfaces.back());
    }

    while(!InputGatherer::containsQuitEvent()) { // temp

        // get inputs from last frame
        for (UniqueDisplayWindow& window : windows) {
            window->gatherInputs();
        }
        Inputs inputs = InputGatherer::getAndClearInputs();

        ///// start game thread
        std::thread gameThread( 

            [&viewInterfaces, &windows, &inputs] () {

                // Handle inputs view interfaces, then in windows
                for (ViewInterface* interface : viewInterfaces) {
                    inputs = interface->handleInputs(inputs);
                }
                for (UniqueDisplayWindow& window : windows) {
                    inputs = window->handleInputs(inputs);
                }

                // Prepare objects for display
                for (ViewInterface* interface : viewInterfaces) {

                    for (UniqueDisplayWindow& window : windows) {

                        window->addViewObjects(
                                interface->getDrawableObjects(), 
                                interface->getAssociatedView()
                        );
                        window->addViewTexts(
                                interface->getDrawableTexts(), 
                                interface->getAssociatedView()
                        );
                    }
                }
            }
        );
        ////// End game thread

        ///// Start Drawing "thread"
        for (UniqueDisplayWindow& window : windows) {
            window->drawScreen();
        }
        //// End drawing "thread"

        gameThread.join();
    }
    
    return 0;

} // end main

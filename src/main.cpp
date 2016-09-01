#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/input_gatherer.h"
#include "battle_room/engine/animation/animation_handler.h"
#include "battle_room/engine/graphics/display_window.h"
#include "battle_room/engine/graphics/get_resource_path.h"

#include <iostream>

using namespace BattleRoom;

int main() {

    // Show Main menu
        // single player
            // Create local server
            // Create menu overlay
            // get drawable objects
            // draw
            // get inputs
            // deal with inputs
            
        // multiplayer
            // Connect/Create network server
            // Create menu overlay
            // get drawable objects
            // draw
            // get inputs
            // deal with inputs
        // options
            // Menu navigation
        // exit


    // set static world view objects <--------- from server
    // in loop
        // clear screen
        // draw static world
        // draw dynamic world <----- from server
        // draw UI
        // draw Menus

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
        // UI look through inputs and remove any used
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

    std::string settings_file = resourcePath + "/startup" + DESCRIPTOR_EXTENSION;
    ResourceDescriptor rd = ResourceDescriptor::readFile(settings_file);

    // --------------------------------------------------
    // GameState gameState;
    
    AnimationHandler::setResourcePath(resourcePath + "/animations/");

    //Menus menus;
    //UserInterfaces uis;
    // server
    //    GameWorld game;

    // Create main components of game
    //ProgramState state;



    // --------------------------------------------------
    // vector<UniqueDisplayWindow> windows;
    // for (ResourceDescriptor window_descriptor : rd.getSubResources("Window")) {
    //        windows.push_back(createDisplayWindow(window_descriptor));
    //          -> window contains views,
    //          -> view contains camera
    // }


    UniqueDisplayWindow window = createDisplayWindow(rd.getSubResource("Window"));

    // Loop until quit
    //while(state.keepGoing()) {

    Inputs inputs = InputGatherer::getAndClearInputs();
    while(!inputs.containsQuitEvent()) { // temp

        // get inputs from last frame
        inputs = InputGatherer::getAndClearInputs();

        ///// start game thread
        //menus.handleInputs(inputs);
            // menues handle any inputs on menu items
            // or escape button for pause, etc.

        //uis.hanldeInputs(inputs);
            // UI Objects hovering in world (but only visible to user) have
            // buttons and things

        //Commands cmds = uis.getCommands():
        //game.handleCommands(cmds);
        //game.update();

        //std::vector<Objects> menuObjects = menus.getObjects();
        //window->addObjectsToView(menuObjects, "Menus");
        //window.addWorldObjects(game.getObjects());
        //window.addUIObjects(uis.getObjects());
        //window.addMenuObjects(menus.getObjects());

        // StateChange = menus.getStateChanges();
        // ----------------------------------------
        // if level change -> window.setStaticObjects(objects);
        // ------------------------------------------
        // for each window
        ////// End game thread

        ///// Start Drawing thread
        window->drawScreen();
        //// End drawing thread
    }
    
    return 0;

} // end main

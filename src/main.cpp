#include "battle_room/engine/graphics/display_window.h"
#include "battle_room/engine/animation/animation_handler.h"

#include <iostream>

using namespace BattleRoom;

int main() {

    std::cout << "Hello World!\n";
    std::string resourcePath = getResourcePath();

    ///// Game States
    // dedicated server
    // Main menu
    // options over main menu
    // options over game
    // game client connected to server
    // game client as server
    // game client as single player
    // single player game paused
    
    AnimationHandler::get().setResourcePath(resourcePath);

    // Create main components of game
    //ProgramState state;
    UniqueDisplayWindow window = createDisplayWindow("window.txt");

    //Menus menus;
    //UserInterfaces uis;
    //GameWorld game;

    // Loop until quit
    //while(state.keepGoing()) {

        //Inputs inputs = window.getInputs();

        //menus.handleInputs(inputs);
        //uis.hanldeInputs(inputs);

        //Commands cmds = uis.getCommands():
        //game.handleCommands(cmds);
        //game.update();

        //window.addWorldObjects(game.getObjects());
        //window.addUIObjects(uis.getObjects());
        //window.addMenuObjects(menus.getObjects());
        //window.drawScreen();
    //}
    // cleanup
    
    return 0;

} // end main

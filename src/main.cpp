#include "battle_room/common/resource_descriptor.h"
#include "battle_room/engine/graphics/display_window.h"
#include "battle_room/engine/animation/animation_handler.h"

#include <iostream>

using namespace BattleRoom;

int main() {

    std::cout << "Hello World!\n";
    std::string resourcePath = getResourcePath();

    std::string settings_file = resourcePath + "/startup" + DESCRIPTOR_EXTENSION;
    ResourceDescriptor rd = ResourceDescriptor::readFile(settings_file);

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
    UniqueDisplayWindow window = createDisplayWindow(rd.getSubResource("Window"));

    //TODO figure out a better way to do camera management
    std::unordered_map<std::string,Camera> cameras;
    window->setCameraMapReference(cameras);
    for (ResourceDescriptor sub : rd.getSubResources("Camera")) {
        cameras.emplace(sub.getValue(), sub);
    }

    for (ResourceDescriptor sub : rd.getSubResources("View")) {
        window->addView(View(sub));
    }

    //Menus menus;
    //UserInterfaces uis;
    //GameWorld game;

    // Loop until quit
    //while(state.keepGoing()) {

    bool tempKeepGoing = true; // temp
    while(tempKeepGoing) { // temp

        Inputs inputs = window->getInputs();
        tempKeepGoing = inputs.m_quit != true; // temp

        //menus.handleInputs(inputs);
            // menues handle any inputs on menu items
            // or escape button for pause, etc.

        // StateChange = menus.getStateChanges();

        //uis.hanldeInputs(inputs);
            // UI Objects hovering in world (but only visible to user) have
            // buttons and things

        //Commands cmds = uis.getCommands():
        //game.handleCommands(cmds);
        //game.update();

        // std::vector<Objects> menuObjects = menus.getObjects();
        // window->addObjectsToView(menuObjects, "Menus");
        //window.addWorldObjects(game.getObjects());
        //window.addUIObjects(uis.getObjects());
        //window.addMenuObjects(menus.getObjects());
        //window.drawScreen();
    }
    
    return 0;

} // end main

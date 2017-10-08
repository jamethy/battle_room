#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/input_gatherer.h"
#include "battle_room/common/animation_handler.h"
#include "battle_room/common/file_utils.h"

#include "battle_room/game/query_world.h"
#include "battle_room/game/objects/object_factory.h"

#include "battle_room/networking/world_updater_factory.h"

#include "battle_room/graphics/display_window.h"

#include "battle_room/user_interface/game_interface.h"

#include <iostream>
#include <fstream>
#include <thread>
#include <algorithm>

using namespace BattleRoom;


std::string getStartupScriptFromArgs(int argc, char **argv);

//TODO find a better way to sort these....
void sortByViewLayer(std::vector<ViewInterface *> &interfaces, ResourceDescriptor settings);


int main(int argc, char **argv) {

    std::cout << "Hello World!\n";

    // Read in the startup script settings file
    std::string settings_file = getStartupScriptFromArgs(argc, argv);
    ResourceDescriptor rd = ResourceDescriptor::readFile(settings_file);

    ObjectFactory::applySettings(rd.getSubResource("ObjectTemplates"));

    // Create the world updater - empty if startup menu, or a server connection,
    // or a local updater
    UniqueWorldUpdater worldUpdater = WorldUpdaterFactory::createWorldUpdater(
            rd.getSubResource("WorldUpdater")
    );


    // Create the windows for displaying - including view/camera setup in each
    std::vector<UniqueDisplayWindow> windows;
    for (ResourceDescriptor windowDescriptor : rd.getSubResources("Window")) {
        windows.push_back(createDisplayWindow(windowDescriptor));
    }


    // Create the game-to-view interfaces (each one points to a view)
    // These produce UI objects that are only seen locally and also
    // handle user inputs - for example, the main view of the world or the minimap
    std::vector<GameInterface> gameInterfaces;
    gameInterfaces.clear();
    for (ResourceDescriptor sub : rd.getSubResources("GameInterface")) {
        gameInterfaces.push_back(GameInterface(sub));
    }


    // Collect the menus. These produce UI objects that are only seen locally and
    // also handle user inputs - they are menus...
    // TODO add menus to vew interfaces


    // Collect the view interfaces (game interfaces and menus) that will need
    // to get inputs from the display and that will send settings to the windows.
    // This is just a vector of pointers to the objects collected above
    std::vector<ViewInterface *> viewInterfaces;
    viewInterfaces.clear();
    for (GameInterface &interface : gameInterfaces) {
        viewInterfaces.push_back(&interface);
    }
    sortByViewLayer(viewInterfaces, rd);


    // Until something adds a quit event to the input gatherer, repeat the loop:
    while (!InputGatherer::containsQuitEvent()) {

        // get inputs from last frame
        for (UniqueDisplayWindow &window : windows) {
            window->gatherInputs();
        }
        Inputs inputs = InputGatherer::getAndClearInputs();


        ///// start game interface thread
        std::thread interfaceThread([&viewInterfaces, &windows, &inputs]() {

            // Handle inputs view interfaces
            for (ViewInterface *interface : viewInterfaces) {
                inputs = interface->handleInputs(inputs);
            }

            // Update world for client
            QueryWorld::updateBuffer();

            // get any settings that need to be applied to windows
            ResourceDescriptor settings;
            for (ViewInterface *interface : viewInterfaces) {
                settings.addSubResources(interface->getNewSettings());
            }
            for (UniqueDisplayWindow &window : windows) {
                window->applySettings(settings);
            }

            // Prepare objects for display
            for (ViewInterface *interface : viewInterfaces) {

                std::string associatedView = interface->getAssociatedView();
                std::vector<DrawableObject> objects = interface->getDrawableObjects();
                std::vector<DrawableText> texts = interface->getDrawableTexts();

                for (UniqueDisplayWindow &window : windows) {
                    window->addViewObjects(objects, associatedView);
                    window->addViewTexts(texts, associatedView);
                }
            }

            // Handle inputs for windows
            for (UniqueDisplayWindow &window : windows) {
                inputs = window->handleInputs(inputs);
            }

            // prevents the CPU from railing
            std::this_thread::sleep_for(std::chrono::milliseconds(25));

        });
        ////// End game interface thread


        ///// Start Drawing "thread" - must be on main thread
        for (UniqueDisplayWindow &window : windows) {
            window->drawScreen();
        }
        //// End drawing "thread"

        interfaceThread.join();

        // Switch buffers that view objects and texts are written to
        for (UniqueDisplayWindow &window : windows) {
            window->switchBuffers();
        }

    }

    return 0;

} // end main

bool fileExists(std::string filename) {
    std::ifstream inFile;
    inFile.open(filename);

    if (!inFile.is_open()) {
        return false;
    } else {
        inFile.close();
        return true;
    }
}

std::string getStartupScriptFromArgs(int argc, char **argv) {

    setResourcePathFromExe(argv[0]);
    std::string startupScript = getResourcePath() + "/startup" + DESCRIPTOR_EXTENSION;

    if (argc > 1) {
        std::string arg = argv[1];

        // try with no additions
        if (fileExists(arg)) {
            startupScript = arg;
        } else {

            // check if file extension is there, and then in res
            if (isEmpty(getFileExtension(arg))) {
                arg += DESCRIPTOR_EXTENSION;
            }

            if (fileExists(arg)) {
                startupScript = arg;
            } else {
                arg = getResourcePath() + "/" + arg;
                if (fileExists(arg)) {
                    startupScript = arg;
                }
            }
        }
        setResourcePathFromStartupScript(startupScript);
    }

    return startupScript;
}

void sortByViewLayer(std::vector<ViewInterface *> &interfaces, ResourceDescriptor settings) {

    // create a map of view names to view layers
    std::unordered_map<std::string, int> viewLayerMap;
    for (ResourceDescriptor window : settings.getSubResources("Window")) {
        for (ResourceDescriptor view : window.getSubResources("View")) {
            int viewLayer = 0;
            if (isNotEmpty(view.getSubResource("Layer").getValue())) {
                viewLayer = std::stoi(view.getSubResource("Layer").getValue());
            }

            viewLayerMap.insert(std::make_pair(view.getValue(), viewLayer));
        }
    }

    // sort by created map
    std::sort(interfaces.begin(), interfaces.end(),
              [&viewLayerMap](ViewInterface *a, ViewInterface *b) {

                  int aLayer = 0, bLayer = 0;
                  if (viewLayerMap.count(a->getAssociatedView()) > 0) {
                      aLayer = viewLayerMap.at(a->getAssociatedView());
                  }
                  if (viewLayerMap.count(b->getAssociatedView()) > 0) {
                      bLayer = viewLayerMap.at(b->getAssociatedView());
                  }
                  return aLayer < bLayer;
              }
    );
}

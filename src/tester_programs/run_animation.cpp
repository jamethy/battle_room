#include "battle_room/engine/graphics/display_window.h"

#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/file_utils.h"
#include "battle_room/engine/animation/animation_handler.h"
#include "battle_room/engine/graphics/get_resource_path.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <chrono>
#include <unordered_map>

using namespace BattleRoom;

using std::vector;
using std::string;
using std::chrono::steady_clock;
using std::chrono::duration;

int main(int argc, char** argv) {

    ////////////////////////////////////////////////////////////////////////////
    // Check the arguments

    string arg = "";

    // check if argument was given, request if not
    if (argc < 2) {
        std::cout << "Please enter animation name or file path: \n";
        std::cin >> arg;
    }
    else {
        arg = argv[1];
    }

    // check file extension, if not there add text
    if (arg.find(DESCRIPTOR_EXTENSION) == string::npos) {
        arg += DESCRIPTOR_EXTENSION;
    }

    std::ifstream infile;

    // see if file exists
    infile.open(arg);
    if (!infile.is_open()) {

        std::cout << "Looking in resource path: " << getResourcePath() << std::endl;
        arg = getResourcePath() + arg;

        infile.open(arg);
        if(!infile.is_open()) {
            std::cerr << "Unable to find file.\n";
            return 0;
        }
    }

    infile.close();



    ////////////////////////////////////////////////////////////////////////////
    // Load the animation


    AnimationHandler::get().setResourcePath(getFilePath(arg));
    Animation animation = AnimationHandler::get().getAnimation(getFileName(arg));

    // Find the largest width and height needed to display full animation
    // This if for camera placement
    meters largestWidth = 0;
    meters largestHeight = 0;
    px largestPxWidth = 0;
    px largestPxHeight = 0;

    for (const Frame& frame : animation.getFrames()) {

        px pxWidth = frame.getBottomRight().getCol() - frame.getTopLeft().getCol();
        px pxHeight = frame.getBottomRight().getRow() - frame.getTopLeft().getRow();
        meters mWidth = pxWidth*frame.getXScale();
        meters mHeight = pxHeight*frame.getYScale();

        if (mWidth > largestWidth) {
            largestWidth = mWidth;
            largestPxWidth = pxWidth;
        }
        if (mHeight > largestHeight) {
            largestHeight = mHeight;
            largestPxHeight = pxHeight;
        }
    }


    // Calulate the camera properties
    double horFov = 1.308985;
    double verFov = 2*atan2(largestHeight*2.0*tan(horFov/2.0), 2.0*largestWidth);
    double camHeight = largestWidth / (2.0*tan(horFov/2.0));

    // Create a mock settings file for easy application
    vector<string> settings;
    settings.push_back("Settings:");
    settings.push_back("    Window: mainWindow");
    settings.push_back("        Width: " + std::to_string(largestPxWidth));
    settings.push_back("        Height: " + std::to_string(largestPxHeight));
    settings.push_back("    Camera: mainCamera");
    settings.push_back("        Position:");
    settings.push_back("            Location: 0,0," + std::to_string(camHeight));
    settings.push_back("        HorizontalFieldOfView: " + std::to_string(horFov));
    settings.push_back("        VerticalFieldOfView: " + std::to_string(verFov));
    settings.push_back("    View: mainView");
    settings.push_back("        Camera: mainCamera");
    settings.push_back("        TopLeft: 0,0");
    settings.push_back("        BottomRight: " 
                            + std::to_string(largestPxHeight) + "," 
                            + std::to_string(largestPxWidth));

    unsigned int start = 0;
    ResourceDescriptor descriptor;
    descriptor.fillFromInput(settings, start);


    // create the window
    UniqueDisplayWindow window = createDisplayWindow(descriptor.getSubResource("Window"));

    // Create the camrea, view, and window
    std::unordered_map<std::string,Camera> cameras;
    for (ResourceDescriptor sub : descriptor.getSubResources("Camera")) {
        if (!cameras.emplace(sub.getValue(), sub).second) {
            std::cerr << "There was a problem placing a camera.\n";
        }
    }
    window->setCameraMapReference(cameras);

    for (ResourceDescriptor sub : descriptor.getSubResources("View")) {
        window->addView(View(sub));
    }

    // Start the clock (resets when it hits the max time of the animation)
    steady_clock::time_point startTime = steady_clock::now();
    seconds maxTime = animation.getFrame(99999999).getEndTime();

    while(window->getInputs().m_quit != true) {

        // Iterate the clock
        steady_clock::time_point newtime = steady_clock::now();
        double diff = std::chrono::duration_cast<duration<double>> (newtime - startTime).count();
        
        // Reset if above max
        if (diff > maxTime) {
            startTime = newtime;
        }

        // Add object to view
        vector<Object> objects;
        Object object(UniqueId::generateNewLocalId());
        object.setAnimation(animation);
        object.setAnimationState(diff);
        //object.position().orientation().rotateAboutZ(60.0*3.14156/180.0);
        objects.push_back(object);
        window->addObjectsToView(objects,"mainView");

        // Draw the screen
        window->drawScreen();

    }

    // cleanup is handled by classes
    return 0;
}

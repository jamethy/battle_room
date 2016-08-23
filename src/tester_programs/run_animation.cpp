#include "battle_room/engine/graphics/display_window.h"

#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/file_utils.h"
#include "battle_room/engine/animation/animation_handler.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <chrono>

using namespace BattleRoom;

using std::vector;
using std::string;
using std::chrono::steady_clock;
using std::chrono::duration;

int main(int argc, char** argv) {

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


    AnimationHandler::get().setResourcePath(getFilePath(arg));
    Animation animation = AnimationHandler::get().getAnimation(getFileName(arg));

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


    double horFov = 1.308985;
    double verFov = 2*atan2(largestHeight*2.0*tan(horFov/2.0), 2.0*largestWidth);
    double camHeight = largestWidth / (2.0*tan(horFov/2.0));

    vector<string> settings;
    settings.push_back("Settings:");
    settings.push_back("    Window: mainWindow");
    settings.push_back("        Width: " + std::to_string(largestPxWidth));
    settings.push_back("        Height: " + std::to_string(largestPxHeight));
    settings.push_back("    Camera:");
    settings.push_back("        Position:");
    settings.push_back("            Location:");
    settings.push_back("                X: 0");
    settings.push_back("                Y: 0");
    settings.push_back("                Z: " + std::to_string(camHeight));
    settings.push_back("        HorizontalFieldOfView: " + std::to_string(horFov));
    settings.push_back("        VerticalFieldOfView: " + std::to_string(verFov));
    settings.push_back("    View: mainView");
    settings.push_back("        Top: 0");
    settings.push_back("        Left: 0");
    settings.push_back("        Bottom: " + std::to_string(largestPxHeight));
    settings.push_back("        Right: " + std::to_string(largestPxWidth));

    unsigned int start = 0;
    ResourceDescriptor descriptor;
    descriptor.fillFromInput(settings, start);

    Camera camera(descriptor.getSubResource("Camera"));

    View view(descriptor.getSubResource("View"));
    view.setCamera(camera);

    UniqueDisplayWindow window = createDisplayWindow(descriptor.getSubResource("Window"));
    window->addView(view);

    seconds maxTime = animation.getFrame(99999999).getEndTime();
    steady_clock::time_point startTime = steady_clock::now();

    while(window->getInputs().m_quit != true) {

        steady_clock::time_point newtime = steady_clock::now();
        double diff = std::chrono::duration_cast<duration<double>> (newtime - startTime).count();
        if (diff > maxTime) {
            startTime = newtime;
        }

        vector<Object> objects;
        Object object;
        object.setAnimation(animation);
        object.setAnimationState(diff);
        objects.push_back(object);

        window->addObjectsToView(objects,"mainView");
        window->drawScreen();

    }


    return 0;
}

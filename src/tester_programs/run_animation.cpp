#include "battle_room/engine/graphics/display_window.h"

#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/file_utils.h"
#include "battle_room/common/input_gatherer.h"
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
        std::cout << "Please enter animation name:\n";
        std::cin >> arg;
    }
    else {
        arg = argv[1];
    }

    std::ifstream infile;

    // see if file exists
    infile.open(getResourcePath() + "/animations/" + arg + DESCRIPTOR_EXTENSION);
    if (!infile.is_open()) {
        std::cerr << "Unable to find file.\n";
        return 0;
    }
    infile.close();



    ////////////////////////////////////////////////////////////////////////////
    // Load the animation

    AnimationHandler::setResourcePath(getResourcePath() + "/animations/");
    Animation animation = AnimationHandler::getAnimation(arg);

    // Find the largest width and height needed to display full animation
    // This if for camera placement
    meters largestWidth = 0;
    meters largestHeight = 0;
    px largestPxWidth = 0;
    px largestPxHeight = 0;

    for (const Frame& frame : animation.getFrames()) {

        px pxWidth = frame.getBottomRight().getCol() - frame.getTopLeft().getCol();
        px pxHeight = frame.getBottomRight().getRow() - frame.getTopLeft().getRow();

        if (frame.getWidth() > largestWidth) {
            largestWidth = frame.getWidth();
            largestPxWidth = pxWidth;
        }
        if (frame.getHeight() > largestHeight) {
            largestHeight = frame.getHeight();
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
    settings.push_back("        View: mainView");
    settings.push_back("            Camera: mainCamera");
    settings.push_back("                Location: 0,0," + std::to_string(camHeight));
    settings.push_back("                Orientation: 1,0,0,0");
    settings.push_back("                HorizontalFieldOfView: " + std::to_string(horFov));
    settings.push_back("                VerticalFieldOfView: " + std::to_string(verFov));
    settings.push_back("            CameraFriction: 0.05");
    settings.push_back("            ZoomInMultiplier: 1");
    settings.push_back("            ZoomOutMultiplier: 1");
    settings.push_back("            TopLeft: 0,0");
    settings.push_back("            BottomRight: " 
                            + std::to_string(largestPxHeight) + "," 
                            + std::to_string(largestPxWidth));

    unsigned int start = 0;
    ResourceDescriptor descriptor;
    descriptor.fillFromInput(settings, start);


    // create the window
    UniqueDisplayWindow window = createDisplayWindow(descriptor.getSubResource("Window"));

    // Start the clock (resets when it hits the max time of the animation)
    steady_clock::time_point startTime = steady_clock::now();
    seconds maxTime = animation.getFrame(99999999).getEndTime();

    DrawableText fpsText;
    fpsText.setText("Sample Text");
    fpsText.setColor(Color(0,0,0,255));
    fpsText.setFont("default.ttf");
    fpsText.setWidth(largestWidth/2.0);
    fpsText.setHeight(fpsText.getWidth()/5.0);
    fpsText.setLocation(Vector3D(
                -fpsText.getWidth(),
                largestHeight/2.0 - fpsText.getHeight()/2.0, 
                0.001
    ));
    steady_clock::time_point lastTime = steady_clock::now();

    Inputs inputs = InputGatherer::getAndClearInputs();
    double slowedFps = 30;
    bool showFps = false;
    while(!InputGatherer::containsQuitEvent()) {

        window->gatherInputs();
        inputs = InputGatherer::getAndClearInputs();
        for (Input& input : inputs) {
            if (input.getMotion() == InputKey::Motion::PressedDown) {
                if (input.getKey() == InputKey::Key::Q) {
                    InputGatherer::addQuitEvent();
                }
                else if (input.getKey() == InputKey::Key::F) {
                    showFps = !showFps;
                }
            }
        }

        window->handleInputs(inputs);

        // Iterate the clock
        steady_clock::time_point newtime = steady_clock::now();
        double diff = std::chrono::duration_cast<duration<double>> (newtime - startTime).count();

        // Reset if above max
        if (diff > maxTime) {
            startTime = newtime;
        }

        // Add object to view
        Object object(UniqueId::generateNewLocalId());
        object.setAnimation(animation);
        object.setAnimationState(diff);
        //Quaternion ori(1,0,0,0);
        //ori.rotateAboutZ(3.141567/2.0);
        //object.setOrientation(ori);
        window->addViewObjects({object},"mainView");

        
        // FPS Display
        double fps = 1.0/std::chrono::duration_cast<duration<double>> (newtime - lastTime).count();

        slowedFps = 0.98*slowedFps + 0.02*fps;
        lastTime = steady_clock::now();

        if (showFps) {
            fpsText.setText("FPS: " + std::to_string((int)slowedFps));
            window->addViewTexts({fpsText},"mainView");
        } else {
            window->addViewTexts(std::vector<DrawableText>(), "mainView");
        }

        // Draw the screen
        window->drawScreen();
    }

    // cleanup is handled by classes
    return 0;
}

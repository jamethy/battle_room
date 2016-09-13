#include "battle_room/graphics/display_window.h"

#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/file_utils.h"
#include "battle_room/common/input_gatherer.h"
#include "battle_room/common/animation_handler.h"

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

    setResourcePathFromExe(argv[0]);

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

    // Create a mock settings file for easy application

    ResourceDescriptor descriptor({
                "Settings:",
                "    Window: mainWindow",
                "        Width: " + std::to_string(largestPxWidth),
                "        Height: " + std::to_string(largestPxHeight),
                "        View: mainView",
                "            CameraMovement:",
                "                MinimumCameraZ: 0.1"
    });


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
                -fpsText.getWidth()/2.0,
                largestHeight/2.0 - fpsText.getHeight()/2.0, 
                0.001
    ));
    steady_clock::time_point lastTime = startTime;

    double slowedFps = -1;
    bool showFps = false;
    unsigned long frame_count = 0;

    while(!InputGatherer::containsQuitEvent()) {

        // Iterate the clock
        steady_clock::time_point newtime = steady_clock::now();
        double diff = std::chrono::duration_cast<duration<double>> (newtime - startTime).count();
        // Reset if above max
        if (diff > maxTime) { startTime = newtime; }

        window->gatherInputs();
        Inputs inputs = InputGatherer::getAndClearInputs();

        // Add object to view
        DrawableObject object;
        object.setAnimation(animation);
        object.setAnimationState(diff);
        window->addViewObjects({object},"mainView");


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

        // FPS Display
        if (std::chrono::duration_cast<duration<double>> (newtime - lastTime).count() > 1) {
            slowedFps = frame_count;
            lastTime = newtime;
            frame_count = 0;
        }

        if (showFps) {
            fpsText.setText("FPS: " + std::to_string((int)slowedFps));
            window->addViewTexts({fpsText},"mainView");
        } 

        ++frame_count;

        // Draw the screen
        window->drawScreen();
        window->switchBuffers();
    }

    // cleanup is handled by classes
    return 0;
}

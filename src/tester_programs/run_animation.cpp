#include "battle_room/engine/graphics/display_window.h"

#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/file_utils.h"

#include <fstream>
#include <iostream>

using namespace BattleRoom;

int main(int argc, char** argv) {

    std::cout << "Hello world.\n";

    std::string arg = "";

    // check if argument was given, request if not
    if (argc < 2) {
        std::cout << "Please enter animation name or file path: \n";
        std::cin >> arg;
    }
    else {
        arg = argv[1];
    }

    // check file extension, if not there add text
    if (arg.find(".txt") == std::string::npos) {
        arg += ".txt";
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
        }
    }

    infile.close();

    readEntireFile(arg);

    UniqueDisplayWindow window = createDisplayWindow("");
    



    return 0;
}

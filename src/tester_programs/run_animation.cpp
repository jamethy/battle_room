#include <iostream>

#include "battle_room/engine/common/resource_descriptor.h"
#include "battle_room/engine/common/file_utils.h"

int main() {

    std::cout << "Hello world.\n";

    std::string filename = "../battle_room/src/tester_programs/res/boy_walking.txt";

    Common::readEntireFile(filename);

    return 0;
}

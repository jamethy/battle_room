#include "controlbaseclass.h"

#include <sstream>
#include <iterator>

ControlBaseClass::ControlBaseClass()
{
    name = "";
}

void ControlBaseClass::change_setting(std::string command)
{
    std::vector<std::string> arguments;
    std::stringstream ss(name+" "+command);
    std::string item;
    while (std::getline(ss,item,' '))
        arguments.push_back(item);

    *outstream << parse_arguments(arguments);
    return;
}

std::ostream* ControlBaseClass::outstream = &std::cout;

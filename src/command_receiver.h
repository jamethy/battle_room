#ifndef COMMAND_RECEIVER_H
#define COMMAND_RECEIVER_H

#include "command.h"

#include <vector>

namespace BattleRoom {

    class CommandReceiver {

    public:

        static void addCommands(const std::vector<Command> &commands);

        static std::vector<Command> getAndClearCommands();

    }; // CommandReceiver class
} // BattleRoom namespace
#endif // COMMAND_RECEIVER_H

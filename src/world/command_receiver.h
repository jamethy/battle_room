#ifndef BATTLE_ROOM_COMMAND_RECEIVER_H
#define BATTLE_ROOM_COMMAND_RECEIVER_H

#include "world/command.h"

#include <vector>

namespace BattleRoom {

    class CommandReceiver {

    public:

        static void addCommands(const std::vector<Command> &commands);

        static std::vector<Command> getAndClearCommands();

        static std::vector<Command> getAndKeepCommands();

    }; // CommandReceiver class
} // BattleRoom namespace
#endif // BATTLE_ROOM_COMMAND_RECEIVER_H

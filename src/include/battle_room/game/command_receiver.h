#ifndef COMMAND_RECEIVER_H
#define COMMAND_RECEIVER_H

#include "battle_room/game/command.h"

#include <vector>

namespace BattleRoom {

class CommandReceiver {

public:

    static void addCommand(const Command& command);

    static std::vector<Command> getAndClearCommands();

}; // CommandReceiver class
} // BattleRoom namespace
#endif // COMMAND_RECEIVER_H

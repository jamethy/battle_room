#include "battle_room/game/command_receiver.h"

using std::vector;

namespace BattleRoom {

vector<Command> m_commandStack;

void CommandReceiver::addCommand(const Command& command) {
    m_commandStack.push_back(command);
}

vector<Command> CommandReceiver::getAndClearCommands() {
    vector<Command> returnCommands = m_commandStack;
    m_commandStack.clear();
    return returnCommands;
}

} // BattleRoom namespace

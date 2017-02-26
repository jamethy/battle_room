#include "battle_room/game/command_receiver.h"

#include <mutex>

using std::vector;

namespace BattleRoom {

    vector<Command> m_commandStack;
    std::mutex m_stackLock;

    void CommandReceiver::addCommands(const vector<Command> &commands) {

        m_stackLock.lock();
        m_commandStack.insert(m_commandStack.end(), commands.begin(), commands.end());
        m_stackLock.unlock();
    }

    vector<Command> CommandReceiver::getAndClearCommands() {

        m_stackLock.lock();
        vector<Command> returnCommands = m_commandStack;
        m_commandStack.clear();
        m_stackLock.unlock();

        return returnCommands;
    }

} // BattleRoom namespace

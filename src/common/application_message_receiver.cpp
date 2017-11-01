#include "battle_room/common/application_message_receiver.h"

#include <mutex>

using std::vector;

namespace BattleRoom {

    bool m_quitEvent = false; ///< Current state of quitting

    vector<ApplicationMessage> m_messageStack;
    std::mutex m_appMsgStackLock;

    void ApplicationMessageReceiver::addMessages(const vector<ApplicationMessage> &messages) {

        m_appMsgStackLock.lock();
        m_messageStack.insert(m_messageStack.end(), messages.begin(), messages.end());
        m_appMsgStackLock.unlock();
    }

    vector<ApplicationMessage> ApplicationMessageReceiver::getAndClearMessages() {

        m_appMsgStackLock.lock();
        vector<ApplicationMessage> returnMessages = m_messageStack;
        m_messageStack.clear();
        m_appMsgStackLock.unlock();

        return returnMessages;
    }

    void ApplicationMessageReceiver::addQuitEvent() {
        m_quitEvent = true;
    }

    bool ApplicationMessageReceiver::containsQuitEvent() {
        return m_quitEvent;
    }

} // BattleRoom namespace

#include "application/application_message_receiver.h"

#include <mutex>

using std::vector;

namespace BattleRoom {

    bool m_quitEvent = false; ///< Current state of quitting

    vector<ApplicationMessage> m_messageStack;
    std::mutex m_appMsgStackLock;

    void ApplicationMessageReceiver::addMessage(const ApplicationMessage &message) {
        m_appMsgStackLock.lock();
        m_messageStack.push_back(message);
        m_appMsgStackLock.unlock();
    }

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

    void ApplicationMessageReceiver::quit() {
        m_quitEvent = true;
    }

    bool ApplicationMessageReceiver::containsQuitEvent() {
        return m_quitEvent;
    }

    void ApplicationMessageReceiver::add(ResourceDescriptor settings) {
        addMessage(ApplicationMessage::add(std::move(settings)));
    }

    void ApplicationMessageReceiver::modify(UniqueId target, ResourceDescriptor settings) {
        addMessage(ApplicationMessage::modify(target, std::move(settings)));
    }

    void ApplicationMessageReceiver::remove(UniqueId target) {
        addMessage(ApplicationMessage::remove(target));
    }

} // BattleRoom namespace


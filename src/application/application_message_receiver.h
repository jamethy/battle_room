#ifndef BATTLE_ROOM_APPLICATION_MESSAGE_RECEIVER_H
#define BATTLE_ROOM_APPLICATION_MESSAGE_RECEIVER_H

#include "application/application_message.h"

namespace BattleRoom {

    class ApplicationMessageReceiver {

    public:

        static void addMessage(const ApplicationMessage &message);

        static void addMessages(const std::vector<ApplicationMessage> &messages);

        static std::vector<ApplicationMessage> getAndClearMessages();

        static void quit();
        
        static void add(ResourceDescriptor settings);
        static void modify(UniqueId target, ResourceDescriptor settings);
        static void remove(UniqueId target);

        /**
         * \brief Returns if a quit event has occurred
         * \return True if the program should be quit
         */
        static bool containsQuitEvent();

    }; // ApplicationMessageReceiver class
} // BattleRoom namespace
#endif // BATTLE_ROOM_APPLICATION_MESSAGE_RECEIVER_H


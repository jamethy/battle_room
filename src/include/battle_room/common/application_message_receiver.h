#ifndef APPLICATION_MESSAGE_RECEIVER_H
#define APPLICATION_MESSAGE_RECEIVER_H

#include "battle_room/common/application_message.h"

namespace BattleRoom {

    class ApplicationMessageReceiver {

    public:

        static void addMessages(const std::vector<ApplicationMessage> &messages);

        static std::vector<ApplicationMessage> getAndClearMessages();

    }; // ApplicationMessageReceiver class
} // BattleRoom namespace
#endif // APPLICATION_MESSAGE_RECEIVER_H


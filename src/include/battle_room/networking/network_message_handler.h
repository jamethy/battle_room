#ifndef NETWORK_MESSAGE_HANDLER_H
#define NETWORK_MESSAGE_HANDLER_H

#include "battle_room/networking/message.h"

namespace BattleRoom {

    /**
     * 
     */
    class NetworkMessageHandler {

    public:

        void handleMessage(const Message& message, BinaryStream& body);

    private:

    }; // NetworkMessageHandler class
} // BattleRoom namespace
#endif // NETWORK_MESSAGE_HANDLER_H


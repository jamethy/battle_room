#ifndef BATTLE_ROOM_NETWORK_MESSAGE_HANDLER_H
#define BATTLE_ROOM_NETWORK_MESSAGE_HANDLER_H

#include "application/message.h"

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
#endif // BATTLE_ROOM_NETWORK_MESSAGE_HANDLER_H


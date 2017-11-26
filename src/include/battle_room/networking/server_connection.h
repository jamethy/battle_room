#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "battle_room/networking/message.h"

#include <memory>

namespace BattleRoom {

    /**
     * 
     */
    class ServerConnection {

    public:

        virtual bool start(int port) = 0;

        virtual void sendMessage(Message& message, BinaryStream& data, UniqueId clientId) = 0;

    }; // ServerConnection class

    typedef std::unique_ptr<ServerConnection> UniqueServerConnection;

    UniqueServerConnection createServerConnection();
} // BattleRoom namespace
#endif // SERVER_CONNECTION_H

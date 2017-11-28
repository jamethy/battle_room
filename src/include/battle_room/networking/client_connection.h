#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "battle_room/networking/message.h"

#include <memory>

namespace BattleRoom {

    /**
     * 
     */
    class ClientConnection {

    public:

        virtual bool connectToServer(std::string host, int port) = 0;

        virtual void sendMessage(Message& message, BinaryStream& bs) = 0;

        void handleMessage(Message& message, BinaryStream& body);

        static void connect(std::string host, int port);
        static void disconnect();
        static void send(Message& message);
        static void send(Message& message, BinaryStream& bs);

    private:

    }; // Client class

    typedef std::unique_ptr<ClientConnection> UniqueClientConnection;

    UniqueClientConnection createClientConnection();

} // BattleRoom namespace
#endif // CLIENT_CONNECTION_H

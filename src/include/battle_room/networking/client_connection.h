#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "battle_room/networking/message.h"

namespace BattleRoom {

    /**
     * 
     */
    class ClientConnection {

    public:

        virtual bool connectToServer(std::string host, int port) = 0;

        virtual void sendMessage(Message& message, BinaryStream& bs) = 0;

    private:

    }; // Client class

    typedef std::unique_ptr<ClientConnection> UniqueClientConnection;

    UniqueClientConnection createClientConnection();

} // BattleRoom namespace
#endif // CLIENT_CONNECTION_H

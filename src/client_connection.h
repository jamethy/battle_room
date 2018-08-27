#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "query_world_updater.h"
#include "message.h"

#include <memory>

namespace BattleRoom {

    /**
     * 
     */
    class ClientConnection : public QueryWorldUpdater {

    public:

        // constructor
        ClientConnection();
        virtual ~ClientConnection() {};

        virtual bool connectToServer(std::string host, int port) = 0;

        virtual void sendMessage(Message& message, BinaryStream& bs) = 0;

        void handleMessage(Message& message, BinaryStream& body);

        // inherited
        virtual void applySettings(ResourceDescriptor settings) override;
        void clientUpdate() override;
        void registerUser(User user) override;

    private:

        BinaryStream m_commandStream;

    }; // Client class
} // BattleRoom namespace
#endif // CLIENT_CONNECTION_H

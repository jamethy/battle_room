#ifndef BATTLE_ROOM_CLIENT_CONNECTION_H
#define BATTLE_ROOM_CLIENT_CONNECTION_H

#include "world/query_world_updater.h"
#include "application/message.h"

#include <memory>

namespace BattleRoom {

    /**
     * 
     */
    class ClientConnection : public QueryWorldUpdater {

    public:

        // constructor
        ClientConnection();

        ~ClientConnection() override = default;;

        virtual bool connectToServer(std::string host, int port) = 0;

        virtual void sendMessage(Message &message, BinaryStream &bs) = 0;

        void handleMessage(Message &message, BinaryStream &body);

        // inherited
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        void clientUpdate() override;

        void registerUser(User user) override;

    private:

        BinaryStream m_commandStream;

    }; // Client class
} // BattleRoom namespace
#endif // BATTLE_ROOM_CLIENT_CONNECTION_H

#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "local_world_updater.h"
#include "message.h"

#include <memory>

namespace BattleRoom {

    /**
     * 
     */
    class ServerConnection : public LocalWorldUpdater {

    public:

        ServerConnection();

        ~ServerConnection() override;

        virtual bool start(int port) = 0;

        virtual void sendMessage(Message &message, BinaryStream &data, UniqueId clientId) = 0;

        void handleMessage(Message &message, BinaryStream &data, UniqueId clientId);

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        void afterUpdate() override;

    private:

        BinaryStream m_responseStream;
        BinaryStream m_worldStream;

    }; // ServerConnection class
} // BattleRoom namespace
#endif // SERVER_CONNECTION_H

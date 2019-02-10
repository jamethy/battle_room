#ifndef BATTLE_ROOM_SERVER_CONNECTION_H
#define BATTLE_ROOM_SERVER_CONNECTION_H

#include "world/local_world_updater.h"
#include "application/message.h"

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
#endif // BATTLE_ROOM_SERVER_CONNECTION_H

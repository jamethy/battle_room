#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "battle_room/game/local_world_updater.h"
#include "battle_room/networking/message.h"

#include <memory>

namespace BattleRoom {

    /**
     * 
     */
    class ServerConnection : public LocalWorldUpdater { 

    public:

        ServerConnection();
        virtual ~ServerConnection();

        virtual bool start(int port) = 0;

        virtual void sendMessage(Message& message, BinaryStream& data, UniqueId clientId) = 0;

        void handleMessage(Message& message, BinaryStream& data, UniqueId clientId);

        virtual void applySettings(ResourceDescriptor settings) override;
        virtual void afterUpdate() override;

    private:

        BinaryStream m_responseStream;
        BinaryStream m_worldStream;

    }; // ServerConnection class
} // BattleRoom namespace
#endif // SERVER_CONNECTION_H

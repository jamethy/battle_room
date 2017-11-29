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

        ServerConnection(ResourceDescriptor settings);
        virtual ~ServerConnection();

        virtual bool start(int port) = 0;

        virtual void sendMessage(Message& message, BinaryStream& data, UniqueId clientId) = 0;

        void handleMessage(Message& message, BinaryStream& data, UniqueId clientId);

    private:
        // list of clients
            // subscribed to

    }; // ServerConnection class
} // BattleRoom namespace
#endif // SERVER_CONNECTION_H

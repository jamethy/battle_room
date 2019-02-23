#ifndef BATTLE_ROOM_CLIENT_CONNECTION_H
#define BATTLE_ROOM_CLIENT_CONNECTION_H

#include "world/query_world_updater.h"
#include "world/local_updating_world.h"
#include "application/message.h"

#include <memory>
#include <thread>
#include <mutex>

namespace BattleRoom {

    /**
     * 
     */
    class ClientConnection : public QueryWorldUpdater {

    public:

        // constructor
        ClientConnection();

        ~ClientConnection() override;

        bool start() override;

        virtual bool connectToServer(std::string host, int port) = 0;

        virtual void sendMessage(Message &message, BinaryStream &bs) = 0;

        virtual void handleMessage(Message &message, BinaryStream &body);

        // inherited
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        void registerUser(User user) override;

    private:

        BinaryStream m_commandStream;

        LocalUpdatingWorld m_world; ///< World that updates itself
        std::mutex m_worldMutex;
        std::thread m_worldThread; ///< Thread to update world on
        std::thread m_commandThread; ///< Thread to update world on
        bool m_keepUpdating; ///< Set to false when ready to destroy

    }; // Client class
} // BattleRoom namespace
#endif // BATTLE_ROOM_CLIENT_CONNECTION_H

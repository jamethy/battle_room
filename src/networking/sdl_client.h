#ifndef BATTLE_ROOM_SDL_CLIENT_H
#define BATTLE_ROOM_SDL_CLIENT_H

#include "networking/client_connection.h"

#include "SDL.h"
#include "SDL_net.h"

#include <thread>

namespace BattleRoom {

    /**
     * 
     */
    class SdlClient : public ClientConnection {

    public:

        // constructors
        explicit SdlClient(ResourceDescriptor settings);

        ~SdlClient() override;

        bool start() override;

        bool connectToServer(std::string host, int port) override;

        void sendMessage(Message &message, BinaryStream &bs) override;

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        std::thread m_receivingThread; ///< Thread to update world on
        bool m_keepReceiving; ///< Set to false when ready to destroy

        TCPsocket m_socket;

        std::string m_host;
        int m_port;

    }; // SdlClient class
} // BattleRoom namespace
#endif // BATTLE_ROOM_SDL_CLIENT_H

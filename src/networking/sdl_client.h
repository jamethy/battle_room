#ifndef SDL_CLIENT_H
#define SDL_CLIENT_H

#include "battle_room/networking/client_connection.h"

#include "SDL.h"
#include "SDL_net.h"

#include <thread>

namespace BattleRoom {

    /**
     * 
     */
    class SdlClient: public ClientConnection {

    public:

        // constructors
        SdlClient(ResourceDescriptor settings);
        ~SdlClient();

        bool connectToServer(std::string host, int port) override;

        void sendMessage(Message& message, BinaryStream& bs) override;

        void applySettings(ResourceDescriptor settings) override;

        std::thread m_receivingThread; ///< Thread to update world on
        bool m_keepReceiving; ///< Set to false when ready to destroy

        TCPsocket m_socket;

    }; // SdlClient class
} // BattleRoom namespace
#endif // SDL_CLIENT_H

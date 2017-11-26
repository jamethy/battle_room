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
        SdlClient();
        ~SdlClient();

        bool connectToServer(std::string host, int port) override;

        void sendMessage(Message& message, BinaryStream& bs) override;


    private:

        std::thread m_updateThread; ///< Thread to update world on
        bool m_keepUpdating; ///< Set to false when ready to destroy

        TCPsocket m_socket;

    }; // SdlClient class
} // BattleRoom namespace
#endif // SDL_CLIENT_H

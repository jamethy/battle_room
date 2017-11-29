#ifndef SDL_SERVER_H
#define SDL_SERVER_H

#include "battle_room/networking/server_connection.h"

#include "SDL.h"
#include "SDL_net.h"

#include <thread>
#include <unordered_map>
#include <mutex>

namespace BattleRoom {

    /**
     * 
     */
    class SdlServer : public ServerConnection {

    public:

        // constructors
        SdlServer(ResourceDescriptor settings);
        ~SdlServer();

        void adjustSocketSet();

        // inherited
        bool start(int port) override;
        void sendMessage(Message& message, BinaryStream& data, UniqueId clientId) override;
        void applySettings(ResourceDescriptor settings) override;
        void afterUpdate() override;

        std::thread m_receivingThread; ///< Thread to update world on
        bool m_keepReceiving; ///< Set to false when ready to destroy

        TCPsocket m_serverSocket;
        std::unordered_map<UniqueId, TCPsocket> m_clientSockets;
        SDLNet_SocketSet m_socketSet;
        std::mutex m_writingLock;
        std::mutex m_listenLock;
    }; // SdlClient class
} // BattleRoom namespace
#endif // SDL_SERVER_H

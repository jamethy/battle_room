#ifndef BATTLE_ROOM_SDL_SERVER_H
#define BATTLE_ROOM_SDL_SERVER_H

#include "networking/server_connection.h"

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
        explicit SdlServer(ResourceDescriptor settings);

        ~SdlServer() override;

        void adjustSocketSet();

        // inherited
        bool start(int port) override;

        void sendMessage(Message &message, BinaryStream &data, UniqueId clientId) override;

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        std::thread m_receivingThread; ///< Thread to update world on
        bool m_keepReceiving; ///< Set to false when ready to destroy

        TCPsocket m_serverSocket;
        std::unordered_map<UniqueId, TCPsocket> m_clientSockets;
        SDLNet_SocketSet m_socketSet;
        std::mutex m_writingLock;
        std::mutex m_listenLock;

        int m_port;
    }; // SdlClient class
} // BattleRoom namespace
#endif // BATTLE_ROOM_SDL_SERVER_H

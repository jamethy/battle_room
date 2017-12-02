
#include "./sdl_server.h"
#include "./sdl_network_helper.h"

// temp
#include "battle_room/game/query_world.h"

#include <iostream>

namespace BattleRoom {

    void listenLoop(SdlServer& server) {

        BinaryStream messageStream(Message::Size);
        BinaryStream dataStream(100);

        std::cout << "Server listening\n";
        server.m_keepReceiving = true;
        while (server.m_keepReceiving) {

            server.m_listenLock.lock();
            int socketsWithData = SDLNet_CheckSockets(server.m_socketSet, 500);

            if(socketsWithData <= 0) {
                server.m_listenLock.unlock();
                continue;
            }

            if (SDLNet_SocketReady(server.m_serverSocket)) {
                --socketsWithData;
                TCPsocket socket = SDLNet_TCP_Accept(server.m_serverSocket);
                if (socket) {

                    std::cout << "Adding new Client\n";
                    UniqueId newClientId = UniqueId::generateNewNetworkId();
                    server.m_writingLock.lock();
                    server.m_clientSockets.emplace(newClientId, socket);
                    server.adjustSocketSet();
                    server.m_writingLock.unlock();
                }
            }

            if(socketsWithData <= 0) {
                server.m_listenLock.unlock();
                continue;
            }

            for (const auto& entry : server.m_clientSockets) {

                if (socketsWithData == 0) {
                    break;
                }

                TCPsocket clientSocket = entry.second;

                if (SDLNet_SocketReady(clientSocket)) {

                    --socketsWithData;

                    Message message;
                    int res = sdlReceiveMessage(message, messageStream, dataStream, clientSocket);
                    if (res <= 0) {

                        std::cout << "Disconnecting client\n";
                        // client probabs disconnect
                        UniqueId clientId = entry.first;
                        server.m_writingLock.lock();
                        server.unregisterUser(clientId);
                        server.m_clientSockets.erase(clientId);
                        server.adjustSocketSet();
                        server.m_writingLock.unlock();

                    } else {
                        server.handleMessage(message, dataStream, entry.first);
                    }
                }
            }
            server.m_listenLock.unlock();
        }
    }

// constructors
    SdlServer::SdlServer(ResourceDescriptor settings) : 
        m_keepReceiving(false) 
    { 
        m_clientSockets.clear();
        applySettings(settings);
        LocalWorldUpdater::start();
    }

    SdlServer::~SdlServer() {
        if (m_keepReceiving) {
            m_keepReceiving = false; 
            if (m_receivingThread.joinable()) {
                m_receivingThread.join();
            }
        }
    }

    bool SdlServer::start(int port) {

        // connect and stuff

        /* initialize SDL */
        if(SDL_Init(0) == -1)
        {
            std::cerr << "SDL_Init: " << SDL_GetError() << std::endl;
            return false;
        }

        /* initialize SDL_net */
        if(SDLNet_Init() == -1)
        {
            std::cerr << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
            return false;
        }

        IPaddress serverIp;
        if(SDLNet_ResolveHost(&serverIp, nullptr, port) == -1)
        {
            std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
            return false;
        }

        m_serverSocket = SDLNet_TCP_Open(&serverIp);
        if(!m_serverSocket)
        {
            std::cerr << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
            return false;
        }

        m_socketSet = SDLNet_AllocSocketSet(1);
        if(SDLNet_TCP_AddSocket(m_socketSet, m_serverSocket) == -1)
        {
            std::cerr << "SDLNet_TCP_AddSocket: " << SDL_GetError() << std::endl;
            return false;
        }

        m_receivingThread = std::thread(listenLoop, std::ref(*this));

        return true;
    }

    void SdlServer::sendMessage(Message& message, BinaryStream& data, UniqueId clientId) {

        if (!clientId.isNetwork()) {
            return;
        }

        if (m_clientSockets.count(clientId) <= 0) {
            std::cerr << "No client of that ID is connected.\n";
            return;
        }
        
        BinaryStream headerStream(Message::Size);

        m_writingLock.lock();
        sdlSendMessage(message, headerStream, data, m_clientSockets.at(clientId));
        m_writingLock.unlock();
    }

    void SdlServer::adjustSocketSet() {

        SDLNet_FreeSocketSet(m_socketSet);
        m_socketSet = SDLNet_AllocSocketSet(m_clientSockets.size() + 1);

        if (SDLNet_TCP_AddSocket(m_socketSet, m_serverSocket) == -1) {
            std::cerr << "SDLNet_TCP_AddSocket: " << SDL_GetError() << std::endl;
            return;
        }

        for (const auto& client : m_clientSockets) {
            if (SDLNet_TCP_AddSocket(m_socketSet, client.second) == -1) {
                std::cerr << "SDLNet_TCP_AddSocket: " << SDL_GetError() << std::endl;
            }
        } 
    }

    void SdlServer::applySettings(ResourceDescriptor settings) {
        ResourceDescriptor portSub = settings.getSubResource("Port");

        if (isNotEmpty(portSub.getValue())) {
            start(stoi(portSub.getValue()));
        }

        ServerConnection::applySettings(settings);
    }
} // BattleRoom namespace

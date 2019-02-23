#include <utility>


#include "networking/sdl_server.h"
#include "networking/sdl_network_helper.h"
#include "common/logger.h"

// temp
#include "world/query_world.h"
#include "sdl_server.h"


namespace BattleRoom {

    void listenLoop(SdlServer &server) {

        BinaryStream messageStream(Message::Size);
        BinaryStream dataStream(100);

        Log::info("Server listening on port ", server.m_port);
        server.m_keepReceiving = true;
        while (server.m_keepReceiving) {

            server.m_listenLock.lock();
            int socketsWithData = SDLNet_CheckSockets(server.m_socketSet, 500);

            if (socketsWithData <= 0) {
                server.m_listenLock.unlock();
                continue;
            }

            if (SDLNet_SocketReady(server.m_serverSocket)) {
                --socketsWithData;
                TCPsocket socket = SDLNet_TCP_Accept(server.m_serverSocket);
                if (socket) {

                    Log::info("Adding new Client");
                    UniqueId newClientId = UniqueId::generateNewNetworkId();
                    server.m_writingLock.lock();
                    server.m_clientSockets.emplace(newClientId, socket);
                    server.adjustSocketSet();
                    server.m_writingLock.unlock();
                }
            }

            if (socketsWithData <= 0) {
                server.m_listenLock.unlock();
                continue;
            }

            for (const auto &entry : server.m_clientSockets) {

                if (socketsWithData == 0) {
                    break;
                }

                TCPsocket clientSocket = entry.second;

                if (SDLNet_SocketReady(clientSocket)) {

                    --socketsWithData;

                    Message message;
                    int res = sdlReceiveTCPMessage(message, messageStream, dataStream, clientSocket);
                    if (res <= 0) {

                        Log::info("Disconnecting client");
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
            m_keepReceiving(false) {
        m_clientSockets.clear();
        applySettings(std::move(settings));
    }

    SdlServer::~SdlServer() {
        if (m_keepReceiving) {
            m_keepReceiving = false;
            if (m_receivingThread.joinable()) {
                m_receivingThread.join();
            }
        }
    }

    bool SdlServer::start() {
        if (!LocalWorldUpdater::start()) {
            return false;
        }

        // connect and stuff

        /* initialize SDL */
        if (SDL_Init(0) == -1) {
            Log::fatal("SDL_Init: ", SDL_GetError());
            return false;
        }

        /* initialize SDL_net */
        if (SDLNet_Init() == -1) {
            Log::fatal("SDLNet_Init: ", SDLNet_GetError());
            return false;
        }

        IPaddress serverIp;
        if (SDLNet_ResolveHost(&serverIp, nullptr, static_cast<Uint16>(m_port)) == -1) {
            Log::fatal("SDLNet_ResolveHost: ", SDLNet_GetError());
            return false;
        }

        m_serverSocket = SDLNet_TCP_Open(&serverIp);
        if (!m_serverSocket) {
            Log::fatal("SDLNet_TCP_Open: ", SDLNet_GetError());
            return false;
        }

        m_socketSet = SDLNet_AllocSocketSet(1);
        if (SDLNet_TCP_AddSocket(m_socketSet, m_serverSocket) == -1) {
            Log::fatal("SDLNet_TCP_AddSocket: ", SDLNet_GetError());
            return false;
        }

        m_receivingThread = std::thread(listenLoop, std::ref(*this));

        return true;
    }

    void SdlServer::sendMessage(Message &message, BinaryStream &data, UniqueId clientId) {

        if (!clientId.isNetwork()) {
            return;
        }

        if (m_clientSockets.count(clientId) <= 0) {
            Log::error("No client of that ID is connected.");
            return;
        }

        BinaryStream headerStream(Message::Size);

        m_writingLock.lock();
        sdlSendTCPMessage(message, headerStream, data, m_clientSockets.at(clientId));
        m_writingLock.unlock();
    }

    void SdlServer::adjustSocketSet() {

        SDLNet_FreeSocketSet(m_socketSet);
        m_socketSet = SDLNet_AllocSocketSet(static_cast<int>(m_clientSockets.size() + 1));

        if (SDLNet_TCP_AddSocket(m_socketSet, m_serverSocket) == -1) {
            Log::error("SDLNet_TCP_AddSocket: ", SDL_GetError());
            return;
        }

        for (const auto &client : m_clientSockets) {
            if (SDLNet_TCP_AddSocket(m_socketSet, client.second) == -1) {
                Log::error("SDLNet_TCP_AddSocket: ", SDL_GetError());
            }
        }
    }

    void SdlServer::applySettings(ResourceDescriptor settings) {
        ResourceDescriptor portSub = settings.getSubResource("Port");

        if (isNotEmpty(portSub.getValue())) {
            m_port = stoi(portSub.getValue());
        }

        ServerConnection::applySettings(settings);
    }

    ResourceDescriptor SdlServer::getSettings() const {
        auto rd = ServerConnection::getSettings();
        rd.emplaceSubResource("Port", std::to_string(m_port));
        return rd;
    }
} // BattleRoom namespace

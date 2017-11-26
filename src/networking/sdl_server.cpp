
#include "./sdl_server.h"

#include <iostream>

namespace BattleRoom {

    UniqueServerConnection createServerConnection() {
        return UniqueServerConnection(new SdlServer());
    }

    void listenLoop(TCPsocket& serverSocket, 
            std::unordered_map<UniqueId, TCPsocket>& clientSockets, 
            SDLNet_SocketSet& socketSet, 
            std::mutex& listenLock, 
            bool &keepUpdating) {

        BinaryStream messageStream(Message::Size);
        BinaryStream dataStream(100);

        while (keepUpdating) {

            listenLock.lock();
            int socketsWithData = SDLNet_CheckSockets(socketSet, 500);

            if(socketsWithData <= 0) {
                continue;
            }

            if (SDLNet_SocketReady(serverSocket)) {
                --socketsWithData;
                TCPsocket socket = SDLNet_TCP_Accept(serverSocket);
                if (socket) {
                    // add to map
                }
            }

            if(socketsWithData <= 0) {
                continue;
            }

            for (const auto& entry : clientSockets) {
                TCPsocket clientSocket = entry.second;
                if (SDLNet_SocketReady(clientSocket)) {

                    // get message
                    // if length is zero, probs a disconnect
                    messageStream.reset();
                    dataStream.reset();

                    messageStream.setDataLength(Message::Size);
                    int bytesRead = SDLNet_TCP_Recv(clientSocket, messageStream.getBuffer(), Message::Size);
                    // haederStream -> setBytesRead

                    if (bytesRead < Message::Size) {
                        std::cerr << "Did not receive full header\n";
                        // server probably down
                        break;
                    }

                    Message message = Message::deserialize(messageStream);

                    if (message.hasBody()) {
                        dataStream.setDataLength(message.getDataSize());
                        bytesRead = SDLNet_TCP_Recv(clientSocket, dataStream.getBuffer(), message.getDataSize());

                        if (bytesRead < message.getDataSize()) {
                            std::cerr << "Did not receive full body\n";
                            continue;
                        }
                    }

                    message.handle(dataStream);

                    if (--socketsWithData == 0) {
                        break;
                    }
                }
            }
            listenLock.unlock();
        }
    }

// constructors
    SdlServer::SdlServer() : 
        m_keepUpdating(false) 
    { 
        m_clientSockets.clear();
    }

    SdlServer::~SdlServer() {
        if (m_keepUpdating) {
            m_keepUpdating = false; 
            if (m_updateThread.joinable()) {
                m_updateThread.join();
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

        m_updateThread = std::thread(listenLoop,
                std::ref(m_serverSocket),
                std::ref(m_clientSockets),
                std::ref(m_socketSet),
                std::ref(m_listenLock),
                std::ref(m_keepUpdating)
                );
    }

    void SdlServer::sendMessage(Message& message, BinaryStream& data, UniqueId clientId) {

        if (m_clientSockets.count(clientId) <= 0) {
            std::cerr << "No client of that ID is connected.\n";
            return;
        }

        m_writingLock.lock();
        TCPsocket socket = m_clientSockets.at(clientId);

        BinaryStream headerStream(Message::Size);
        message.serialize(headerStream);
        int bytesWritten = SDLNet_TCP_Send(socket, headerStream.getBuffer(), headerStream.getLength());
        if (bytesWritten < headerStream.getLength()) {
            //freak out
            std::cerr << "Did not send full header\n";
            m_writingLock.unlock();
            return;
        }

        bytesWritten = SDLNet_TCP_Send(socket, data.getBuffer(), data.getLength());
        if (bytesWritten < data.getLength()) {
            //freak out
            std::cerr << "Did not send full body\n";
            m_writingLock.unlock();
            return;
        }
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

    void SdlServer::addClient(UniqueId id, TCPsocket socket) {
        m_writingLock.lock();
        m_listenLock.lock();

        m_clientSockets.emplace(id, socket);
        adjustSocketSet();

        m_writingLock.unlock();
        m_listenLock.unlock();
    }

    void SdlServer::removeClient(UniqueId id) {
        m_writingLock.lock();
        m_listenLock.lock();

        m_clientSockets.erase(id);
        adjustSocketSet();

        m_writingLock.unlock();
        m_listenLock.unlock();
    }
} // BattleRoom namespace

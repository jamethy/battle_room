
#include "./sdl_server.h"

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

                    // tell app
                }
            }

            if(socketsWithData <= 0) {
                server.m_listenLock.unlock();
                continue;
            }

            for (const auto& entry : server.m_clientSockets) {
                TCPsocket clientSocket = entry.second;
                if (SDLNet_SocketReady(clientSocket)) {

                    // get message
                    // if length is zero, probs a disconnect
                    messageStream.reset();
                    dataStream.reset();

                    messageStream.setDataLength(Message::Size);
                    int bytesRead = SDLNet_TCP_Recv(clientSocket, messageStream.getBuffer(), Message::Size);

                    if (bytesRead < (int)Message::Size) {
                        std::cout << "Did not receive full header - disconnecting client\n";
                        // client probabs disconnect
                        UniqueId clientId = entry.first;
                        server.m_writingLock.lock();
                        server.m_clientSockets.erase(clientId);
                        server.adjustSocketSet();
                        server.m_writingLock.unlock();

                        // tell app
                    }

                    Message message = Message::deserialize(messageStream);

                    if (message.getHeaderHash() != message.hash()) {
                        std::cerr << "Header hash did not meet calculations\n";
                        continue;
                    }

                    if (message.hasBody()) {
                        dataStream.setDataLength(message.getDataSize());
                        bytesRead = SDLNet_TCP_Recv(clientSocket, dataStream.getBuffer(), message.getDataSize());

                        if (bytesRead < (int)message.getDataSize()) {
                            std::cerr << "Did not receive full body\n";
                            continue;
                        }

                        if (message.getBodyHash() != dataStream.hash()) {
                            std::cerr << "Body hash did not meet calculations\n";
                            continue;
                        }
                    }

                    server.handleMessage(message, dataStream, entry.first);

                    if (--socketsWithData == 0) {
                        break;
                    }
                }
            }
            server.m_listenLock.unlock();
        }
    }

// constructors
    SdlServer::SdlServer(ResourceDescriptor settings) : 
        ServerConnection(settings),
        m_keepReceiving(false) 
    { 
        m_clientSockets.clear();
        applySettings(settings);
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

        if (m_clientSockets.count(clientId) <= 0) {
            std::cerr << "No client of that ID is connected.\n";
            return;
        }

        message.setDataSize(data.getLength());
        message.setBodyHash(data.hash());

        BinaryStream headerStream(Message::Size);
        message.serialize(headerStream);

        m_writingLock.lock();
        TCPsocket socket = m_clientSockets.at(clientId);
        int bytesWritten = SDLNet_TCP_Send(socket, headerStream.getBuffer(), headerStream.getLength());
        if (bytesWritten < (int)headerStream.getLength()) {
            //freak out
            std::cerr << "Did not send full header\n";
            m_writingLock.unlock();
            return;
        }

        bytesWritten = SDLNet_TCP_Send(socket, data.getBuffer(), data.getLength());
        if (bytesWritten < (int)data.getLength()) {
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

    void SdlServer::applySettings(ResourceDescriptor settings) {
        ResourceDescriptor portSub = settings.getSubResource("Port");

        if (isNotEmpty(portSub.getValue())) {
            start(stoi(portSub.getValue()));
        }
    }


    // temp move to server conn
    void SdlServer::afterUpdate() {

        BinaryStream resBody(8000);
        Message response;
        response.setMessageType(GetWorldResponse);
        QueryWorld::serialize(resBody);
        for (const auto& client : m_clientSockets) {
            sendMessage(response, resBody, client.first);
        }
    }

} // BattleRoom namespace

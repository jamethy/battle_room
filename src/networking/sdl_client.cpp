
#include "./sdl_client.h"

#include <iostream>

namespace BattleRoom {

    void listenLoop(SdlClient& client) {

        SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
        if(SDLNet_TCP_AddSocket(socketSet, client.m_socket) == -1)
        {
            std::cerr << "SDLNet_TCP_AddSocket: " << SDL_GetError() << std::endl;
            return;
        }

        std::cout << "Listening for server\n";

        BinaryStream messageStream(Message::Size);
        BinaryStream dataStream(10000);

        while (client.m_keepReceiving) {
            if(SDLNet_CheckSockets(socketSet, 500) > 0 && SDLNet_SocketReady(client.m_socket)) {

                messageStream.reset();
                dataStream.reset();

                messageStream.setDataLength(Message::Size);
                int bytesRead = SDLNet_TCP_Recv(client.m_socket, messageStream.getBuffer(), Message::Size);
                // haederStream -> setBytesRead

                if (bytesRead < (int)Message::Size) {
                    std::cerr << "Did not receive full header\n";
                    // server probably down
                    break;
                }

                Message message = Message::deserialize(messageStream);

                if (message.getHeaderHash() != message.hash()) {
                    std::cerr << "Header hash did not meet calculations\n";
                    continue;
                }

                if (message.hasBody()) {
                    dataStream.setDataLength(message.getDataSize());
                    bytesRead = SDLNet_TCP_Recv(client.m_socket, dataStream.getBuffer(), message.getDataSize());

                    if (bytesRead < (int)message.getDataSize()) {
                        std::cerr << "Did not receive full body\n";
                        continue;
                    }

                    if (message.getBodyHash() != dataStream.hash()) {
                        std::cerr << "Body hash did not meet calculations\n";
                        std::cerr << "header: " << message.getBodyHash() << " bs: " << dataStream.hash() << std::endl;
                        continue;
                    }
                }

                client.handleMessage(message, dataStream);
            }
        }
    }

// constructors
    SdlClient::SdlClient(ResourceDescriptor settings) : 
        m_keepReceiving(false) 
    {
        applySettings(settings);
    }

    SdlClient::~SdlClient() {
        if (m_keepReceiving) {
            m_keepReceiving = false; 
            if (m_receivingThread.joinable()) {
                m_receivingThread.join();
            }
        }
    }

    bool SdlClient::connectToServer(std::string host, int port) {

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
        if(SDLNet_ResolveHost(&serverIp, host.c_str(), port) == -1)
        {
            std::cerr << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
            return false;
        }

        m_socket = SDLNet_TCP_Open(&serverIp);
        if(!m_socket)
        {
            std::cerr << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
            return false;
        }

        m_keepReceiving = true;
        m_receivingThread = std::thread(listenLoop, std::ref(*this));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        return true;
    }

    void SdlClient::sendMessage(Message& message, BinaryStream& bs) {

        if (!m_socket) {
                std::cerr << "Socket has not been connected\n";
        } else {

            message.setDataSize(bs.getLength());
            message.setBodyHash(bs.hash());

            BinaryStream messageStream(Message::Size);
            message.serialize(messageStream);

            int bytesWritten = SDLNet_TCP_Send(m_socket, messageStream.getBuffer(), messageStream.getLength());
            if (bytesWritten < (int)Message::Size) {
                //freak out
                std::cerr << "Did not send full header\n";
                return;
            }

            if (message.hasBody()) {
                bytesWritten = SDLNet_TCP_Send(m_socket, bs.getBuffer(), bs.getLength());
                if (bytesWritten < (int)bs.getLength()) {
                    //freak out
                    std::cerr << "Did not send full body\n";
                    return;
                }
            }
        }
    }

    void SdlClient::applySettings(ResourceDescriptor settings) {
        ResourceDescriptor hostSub = settings.getSubResource("Host");
        ResourceDescriptor portSub = settings.getSubResource("Port");

        if (isNotEmpty(hostSub.getValue()) && isNotEmpty(portSub.getValue())) {
            connectToServer(hostSub.getValue(), stoi(portSub.getValue()));
        }
    }

} // BattleRoom namespace

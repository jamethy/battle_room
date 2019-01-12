
#include "./sdl_client.h"
#include "./sdl_network_helper.h"
#include "Logger.h"

#include <sstream>

namespace BattleRoom {

    void listenLoop(SdlClient &client) {

        SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
        if (SDLNet_TCP_AddSocket(socketSet, client.m_socket) == -1) {
            std::stringstream ss;
            ss << "SDLNet_TCP_AddSocket: " << SDL_GetError();
            Log::error(ss.str());
            return;
        }

        Log::info("Listening for server");

        BinaryStream messageStream(Message::Size);
        BinaryStream dataStream(10000);

        while (client.m_keepReceiving) {
            if (SDLNet_CheckSockets(socketSet, 500) > 0 && SDLNet_SocketReady(client.m_socket)) {

                Message message;
                if (sdlReceiveMessage(message, messageStream, dataStream, client.m_socket) > 0) {
                    client.handleMessage(message, dataStream);
                }
            }
        }
    }

// constructors
    SdlClient::SdlClient(ResourceDescriptor settings) :
            m_keepReceiving(false) {
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
        if (SDL_Init(0) == -1) {
            std::stringstream ss;
            ss << "SDL_Init: " << SDL_GetError();
            Log::error(ss.str());
            return false;
        }

        /* initialize SDL_net */
        if (SDLNet_Init() == -1) {
            std::stringstream ss;
            ss << "SDLNet_Init: " << SDLNet_GetError();
            Log::error(ss.str());
            return false;
        }

        IPaddress serverIp;
        if (SDLNet_ResolveHost(&serverIp, host.c_str(), port) == -1) {
            std::stringstream ss;
            ss << "SDLNet_ResolveHost: " << SDLNet_GetError();
            Log::error(ss.str());
            return false;
        }

        m_socket = SDLNet_TCP_Open(&serverIp);
        if (!m_socket) {
            std::stringstream ss;
            ss << "SDLNet_TCP_Open: " << SDLNet_GetError();
            Log::error(ss.str());
            return false;
        }

        m_keepReceiving = true;
        m_receivingThread = std::thread(listenLoop, std::ref(*this));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        return true;
    }

    void SdlClient::sendMessage(Message &message, BinaryStream &bs) {

        if (!m_socket) {
            Log::error("Socket has not been connected");
        } else {

            BinaryStream headerStream(Message::Size);
            sdlSendMessage(message, headerStream, bs, m_socket);
        }
    }

    void SdlClient::applySettings(ResourceDescriptor settings) {
        ResourceDescriptor hostSub = settings.getSubResource("Host");
        ResourceDescriptor portSub = settings.getSubResource("Port");

        if (isNotEmpty(hostSub.getValue()) && isNotEmpty(portSub.getValue())) {
            connectToServer(hostSub.getValue(), stoi(portSub.getValue()));
        }

        ClientConnection::applySettings(settings);
    }

} // BattleRoom namespace
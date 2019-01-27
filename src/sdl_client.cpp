#include <utility>


#include "logger.h"
#include "sdl_client.h"
#include "sdl_network_helper.h"

namespace BattleRoom {

    void listenLoop(SdlClient &client) {

        SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
        if (SDLNet_TCP_AddSocket(socketSet, client.m_socket) == -1) {
            Log::error("SDLNet_TCP_AddSocket: ", SDL_GetError());
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
        applySettings(std::move(settings));
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
            Log::error("SDL_Init: ", SDL_GetError());
            return false;
        }

        /* initialize SDL_net */
        if (SDLNet_Init() == -1) {
            Log::error("SDLNet_Init: ", SDLNet_GetError());
            return false;
        }

        IPaddress serverIp;
        if (SDLNet_ResolveHost(&serverIp, host.c_str(), static_cast<Uint16>(port)) == -1) {
            Log::error("SDLNet_ResolveHost: ", SDLNet_GetError());
            return false;
        }

        m_socket = SDLNet_TCP_Open(&serverIp);
        if (!m_socket) {
            Log::error("SDLNet_TCP_Open: ", SDLNet_GetError());
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
            m_host = hostSub.getValue();
            m_port = stoi(portSub.getValue());
            connectToServer(m_host, m_port);
        }

        ClientConnection::applySettings(settings);
    }

    ResourceDescriptor SdlClient::getSettings() const {
        auto rd = ClientConnection::getSettings();
        auto subs = rd.getSubResources();

        subs.emplace_back("Host", m_host);
        subs.emplace_back("Port", std::to_string(m_port));

        rd.setSubResources(subs);
        return rd;
    }

} // BattleRoom namespace

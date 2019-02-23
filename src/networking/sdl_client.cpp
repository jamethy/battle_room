#include "common/logger.h"
#include "networking/sdl_client.h"
#include "networking/sdl_network_helper.h"
#include "sdl_client.h"


namespace BattleRoom {

    void listenLoop(SdlClient &client) {

        SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
        if (SDLNet_TCP_AddSocket(socketSet, client.getSocket()) == -1) {
            Log::error("SDLNet_TCP_AddSocket: ", SDL_GetError());
            return;
        }

        Log::info("Listening for server");

        BinaryStream messageStream(Message::Size);
        BinaryStream dataStream(10000);

        while (client.keepReceiving()) {
            if (SDLNet_CheckSockets(socketSet, 500) > 0 && SDLNet_SocketReady(client.getSocket())) {

                Message message;
                if (sdlReceiveTCPMessage(message, messageStream, dataStream, client.getSocket()) > 0) {
                    client.handleMessage(message, dataStream);
                }
            }
        }
    }

// constructors
    SdlClient::SdlClient(ResourceDescriptor settings) :
            m_keepReceiving(false),
            m_socket(nullptr),
            m_host(""),
            m_port(0) {
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
            sdlSendTCPMessage(message, headerStream, bs, m_socket);
        }
    }

    void SdlClient::applySettings(ResourceDescriptor settings) {
        ResourceDescriptor hostSub = settings.getSubResource("Host");
        ResourceDescriptor portSub = settings.getSubResource("Port");


        if (isNotEmpty(hostSub.getValue()) && isNotEmpty(portSub.getValue())) {
            m_host = hostSub.getValue();
            m_port = stoi(portSub.getValue());
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

    bool SdlClient::start() {
        return ClientConnection::start() && connectToServer(m_host, m_port);
    }

    bool SdlClient::keepReceiving() const {
        return m_keepReceiving;
    }

    TCPsocket SdlClient::getSocket() const {
        return m_socket;
    }

} // BattleRoom namespace

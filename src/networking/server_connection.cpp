#include "battle_room/networking/server_connection.h"
#include "battle_room/game/query_world.h"
#include "battle_room/game/command_receiver.h"

#include <iostream>

namespace BattleRoom {

    void handleCommandsRequest(BinaryStream& body) {
        int count = body.readInt();
        std::vector<Command> commands(count);
        for (int i = 0; i < count; ++i) {
            commands[i] = Command::deserialize(body);
        }
        CommandReceiver::addCommands(commands);
    }

    void ServerConnection::handleMessage(Message& message, BinaryStream& body, UniqueId clientId) {
        BinaryStream resBody(8000);
        Message response;
        switch (message.getMessageType()) {

            case GetWorldRequest:
                QueryWorld::serialize(resBody);
                response.setMessageType(GetWorldResponse);
                sendMessage(response, resBody, clientId);
                break;

            case PostCommandsRequest:
                handleCommandsRequest(body);
                break;

            case GetWorldResponse:
            default:
                // unrecognized
                break;
        }

    }

    static UniqueServerConnection m_serverConn = nullptr;

    static BinaryStream m_emptyServerStream(1);

    void ServerConnection::startServer(int port) {
        m_serverConn = createServerConnection();
        m_serverConn->start(port);
    }

    void ServerConnection::stopServer() {
        m_serverConn = nullptr;
    }

    void ServerConnection::send(Message& message, UniqueId clientId) {
        if (m_serverConn) {
            m_serverConn->sendMessage(message, m_emptyServerStream, clientId);
        }
    }

    void ServerConnection::send(Message& message, BinaryStream& bs, UniqueId clientId) {
        if (m_serverConn) {
            m_serverConn->sendMessage(message, bs, clientId);
        }
    }

} // BattleRoom namespace

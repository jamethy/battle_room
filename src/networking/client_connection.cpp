#include "battle_room/networking/client_connection.h"
#include "battle_room/game/query_world.h"

#include <iostream>

namespace BattleRoom {

    void ClientConnection::handleMessage(Message& message, BinaryStream& body) {
        BinaryStream resBody(8000);
        Message response;
        switch (message.getMessageType()) {

            case GetWorldResponse:
                QueryWorld::updateCopyWorld(World::deserialize(body));
                break;

            case PostCommandsRequest:
            case GetWorldRequest:
                break;

            default:
                // unrecognized
                break;
        }

    }

    static UniqueClientConnection m_connection = nullptr;

    static BinaryStream m_emptyStream(1);

    void ClientConnection::connect(std::string host, int port) {
        m_connection = createClientConnection();
        m_connection->connectToServer(host, port);
    }

    void ClientConnection::disconnect() {
        m_connection = nullptr;
    }

    void ClientConnection::send(Message& message) {
        if (m_connection) {
            m_connection->sendMessage(message, m_emptyStream);
        }
    }

    void ClientConnection::send(Message& message, BinaryStream& bs) {
        if (m_connection) {
            m_connection->sendMessage(message, bs);
        }
    }


} // BattleRoom namespace


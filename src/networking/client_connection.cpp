#include "battle_room/networking/client_connection.h"
#include "battle_room/game/query_world.h"
#include "battle_room/game/command_receiver.h"

#include <iostream>

namespace BattleRoom {

    ClientConnection::ClientConnection() :
        m_commandStream(BinaryStream(400))
    {}

    void ClientConnection::handleMessage(Message& message, BinaryStream& body) {
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

    void ClientConnection::clientUpdate() {

        const auto commands = CommandReceiver::getAndClearCommands();

        if (commands.size() > 0) {

            m_commandStream.reset();
            m_commandStream.writeInt(commands.size());

            for (const auto& cmd : commands) {
                cmd.serialize(m_commandStream);
            }

            Message msg;
            msg.setMessageType(MessageType::PostCommandsRequest);

            sendMessage(msg, m_commandStream);
        }
    }
} // BattleRoom namespace

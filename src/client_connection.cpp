#include "client_connection.h"
#include "query_world.h"
#include "command_receiver.h"

namespace BattleRoom {

    ClientConnection::ClientConnection() :
        m_commandStream(BinaryStream(400))
    {}

    void ClientConnection::handleMessage(Message& message, BinaryStream& body) {

        MessageType requestType = message.getMessageType();

        if (MessageType::GetWorldResponse == requestType) {

            QueryWorld::updateCopyWorld(World::deserialize(body));

        } else if (MessageType::RegisterUserResponse == requestType) {
            User user = User::deserialize(body);
            QueryWorld::setClientId(user.getUniqueId());
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

    void ClientConnection::registerUser(User user) {
        Message message(MessageType::RegisterUserRequest);
        m_commandStream.reset();
        user.serialize(m_commandStream);
        sendMessage(message, m_commandStream);
    }

    void ClientConnection::applySettings(ResourceDescriptor settings) {
        QueryWorldUpdater::applySettings(settings);
    }

} // BattleRoom namespace

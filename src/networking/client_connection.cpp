#include "networking/client_connection.h"
#include "world/query_world.h"
#include "world/command_receiver.h"

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

        if (!commands.empty()) {

            m_commandStream.reset();
            m_commandStream.writeInt(static_cast<int>(commands.size()));

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

    ResourceDescriptor ClientConnection::getSettings() const {
        auto rd = QueryWorldUpdater::getSettings();
        rd.setValue("Client");
        return rd;
    }

} // BattleRoom namespace

#include "battle_room/networking/server_connection.h"
#include "battle_room/game/query_world.h"
#include "battle_room/game/command_receiver.h"

namespace BattleRoom {


    ServerConnection::ServerConnection() :
        m_responseStream(BinaryStream(8000))
    { }

    ServerConnection::~ServerConnection() { }

    void ServerConnection::handleMessage(Message& message, BinaryStream& body, UniqueId clientId) {
        Message response;
        m_responseStream.reset();

        MessageType requestType = message.getMessageType();

        if (MessageType::GetWorldRequest == requestType) {

            QueryWorld::serialize(m_responseStream);
            response.setMessageType(GetWorldResponse);
            sendMessage(response, m_responseStream, clientId);

        } else if (MessageType::PostCommandsRequest == requestType) {
            
            int count = body.readInt();
            std::vector<Command> commands(count);
            for (int i = 0; i < count; ++i) {
                commands[i] = Command::deserialize(body);
            }
            CommandReceiver::addCommands(commands);

        } else if (MessageType::RegisterUserRequest == requestType) {
            // handle
            User user = User::deserialize(body);
            user.setUniqueId(clientId);
            registerUser(user);

            // respnose
            Message message(MessageType::RegisterUserResponse);
            user.serialize(m_responseStream);
            sendMessage(message, m_responseStream, clientId);
        }
        // else unrecognized

    }

    void ServerConnection::applySettings(ResourceDescriptor settings) {
        LocalWorldUpdater::applySettings(settings);
    }
} // BattleRoom namespace

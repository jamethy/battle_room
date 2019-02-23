#include <common/logger.h>
#include "networking/server_connection.h"
#include "world/query_world.h"
#include "world/command_receiver.h"
#include "server_connection.h"


namespace BattleRoom {


    ServerConnection::ServerConnection() :
        m_responseStream(8000),
        m_worldStream(16000)
    { }

    ServerConnection::~ServerConnection() = default;

    void ServerConnection::handleMessage(Message& message, BinaryStream& body, UniqueId clientId) {
        m_responseStream.reset();

        MessageType requestType = message.getMessageType();

        if (MessageType::GetWorldRequest == requestType) {

            QueryWorld::serialize(m_responseStream);

            Message response(GetWorldResponse);
            sendMessage(response, m_responseStream, clientId);

        } else if (MessageType::PostCommandsRequest == requestType) {
            
            int count = body.readInt();
            std::vector<Command> commands(static_cast<unsigned long>(count));
            for (int i = 0; i < count; ++i) {
                commands[i] = Command::deserialize(body);
                if (commands[i].getType() != Aim) {
                    Log::debug(commands[i].toString());
                }
            }
            CommandReceiver::addCommands(commands);

        } else if (MessageType::RegisterUserRequest == requestType) {
            // handle
            User user = User::deserialize(body);
            user.setUniqueId(clientId);
            registerUser(user);

            // respnose
            Message response(MessageType::RegisterUserResponse);
            user.serialize(m_responseStream);
            sendMessage(response, m_responseStream, clientId);
        }
        // else unrecognized

    }

    void ServerConnection::afterUpdate() {

        LocalWorldUpdater::afterUpdate();

        Message msg(GetWorldResponse);
        m_worldStream.reset();
        QueryWorld::serialize(m_worldStream);

        // todo parallelze
        for (const auto& user : m_users) {
            sendMessage(msg, m_worldStream, user.getUniqueId());
        }
    }

    ResourceDescriptor ServerConnection::getSettings() const {
        auto rd = LocalWorldUpdater::getSettings();
        rd.setValue("Server");
        return rd;
    }

} // BattleRoom namespace

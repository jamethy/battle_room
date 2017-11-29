#include "battle_room/networking/server_connection.h"
#include "battle_room/game/query_world.h"
#include "battle_room/game/command_receiver.h"

#include <iostream>

namespace BattleRoom {


    ServerConnection::ServerConnection(ResourceDescriptor settings) :
        LocalWorldUpdater(settings)
    { }

    ServerConnection::~ServerConnection() { }

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
} // BattleRoom namespace

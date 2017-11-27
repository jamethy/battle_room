#include "battle_room/networking/client_connection.h"

#include <iostream>

using namespace BattleRoom;

int main() {
    std::cout << "Hello world\n";

    UniqueClientConnection client = createClientConnection();
    if (client->connectToServer("localhost", 8080)) {

        Message message;
        message.setMessageType(MessageType::GetWorld);

        BinaryStream bs(1);
        client->sendMessage(message, bs);
    }

    return 0;
}

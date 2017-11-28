#include "battle_room/networking/client_connection.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace BattleRoom;

int main() {
    std::cout << "Hello world\n";

    UniqueClientConnection client = createClientConnection();
    if (client->connectToServer("localhost", 8080)) {

        Message message;
        message.setMessageType(MessageType::GetWorldRequest);

        BinaryStream bs(1);
        client->sendMessage(message, bs);
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(20));


    return 0;
}

#ifndef SDL_NETWORK_HELPER_H
#define SDL_NETWORK_HELPER_H

#include "battle_room/common/binary_stream.h"
#include "battle_room/networking/message.h"

#include "SDL.h"
#include "SDL_net.h"

namespace BattleRoom {

    int sdlReceive(TCPsocket socket, BinaryStream& bs, int maxLength);

    int sdlWrite(TCPsocket socket, BinaryStream& bs);

    int sdlSendMessage(Message& message, BinaryStream& messageStream, BinaryStream& body, TCPsocket socket);

    int sdlReceiveMessage(Message& message, BinaryStream& messageStream, BinaryStream& dataStream, TCPsocket socket);

} // BattleRoom namespace
#endif // SDL_NETWORK_HELPER_H

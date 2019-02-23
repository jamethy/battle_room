#ifndef BATTLE_ROOM_SDL_NETWORK_HELPER_H
#define BATTLE_ROOM_SDL_NETWORK_HELPER_H

#include "common/binary_stream.h"
#include "application/message.h"

#include "SDL.h"
#include "SDL_net.h"

namespace BattleRoom {

    int sdlReceive(TCPsocket socket, BinaryStream& bs, int maxLength);

    int sdlWrite(TCPsocket socket, BinaryStream& bs);

    int sdlSendTCPMessage(Message &message, BinaryStream &messageStream, BinaryStream &body, TCPsocket socket);

    int sdlReceiveTCPMessage(Message &message, BinaryStream &messageStream, BinaryStream &dataStream, TCPsocket socket);

} // BattleRoom namespace
#endif // BATTLE_ROOM_SDL_NETWORK_HELPER_H

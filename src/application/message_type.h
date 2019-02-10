#ifndef BATTLE_ROOM_MESSAGE_TYPE_H
#define BATTLE_ROOM_MESSAGE_TYPE_H

namespace BattleRoom {

    enum MessageType {
        InvalidRequest = 0,
        GetWorldRequest,
        GetWorldResponse,
        PostCommandsRequest,
        RegisterUserRequest,
        RegisterUserResponse,
    }; // MessageType enum
} // BattleRoom namespace
#endif // BATTLE_ROOM_MESSAGE_TYPE_H

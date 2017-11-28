#ifndef MESSAGE_TYPE_H
#define MESSAGE_TYPE_H

namespace BattleRoom {

    enum MessageType {
        InvalidRequest = 0,
        GetWorldRequest,
        GetWorldResponse,
        PostCommandsRequest
    }; // MessageType enum
} // BattleRoom namespace
#endif // MESSAGE_TYPE_H

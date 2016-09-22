#ifndef MESSAGE_H
#define MESSAGE_H

#include "battle_room/networking/message_type.h"

namespace BattleRoom {

unsigned long MAX_MESSAGE_LENGTH = 1024;

/**
 * Message object that can be sent over the network
 */
class Message {

public:

    virtual MessageType getMessageType() = 0;

    virtual void copyFrom(void* buffer) = 0;

    virtual void copyTo(void* buffer) = 0;

}; // Message class
} // BattleRoom namespace
#endif // MESSAGE_H

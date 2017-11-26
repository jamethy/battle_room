#ifndef MESSAGE_H
#define MESSAGE_H

#include "battle_room/networking/message_type.h"
#include "battle_room/common/binary_stream.h"

namespace BattleRoom {

    /**
     * 
     */
    class Message {

    public:

        void handle(BinaryStream& bs);

        // getters and setters
        void setMessageId(UniqueId id);
        void setMessageType(MessageType type);
        void setDataSize(size_t dataSize);

        UniqueId getMessageId() const;
        MessageType getMessageType() const;
        size_t getDataSize() const;
        bool hasBody() const;

        void serialize(BinaryStream& bs);
        static Message deserialize(BinaryStream& bs) const;

        static const size_t Size = sizeof(int) + sizeof(int) + sizeof(size_t);

    private:

        UniqueId m_messageId;
        // auth
        MessageType m_type;
        size_t m_dataSize;

    }; // Message class
} // BattleRoom namespace
#endif // MESSAGE_H

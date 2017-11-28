#ifndef MESSAGE_H
#define MESSAGE_H

#include "battle_room/networking/message_type.h"
#include "battle_room/common/unique_id.h"
#include "battle_room/common/binary_stream.h"

namespace BattleRoom {

    /**
     * 
     */
    class Message {

    public:

        // constructors
        Message();

        int hash() const;

        // getters and setters
        void setSourceId(UniqueId id);
        void setMessageType(MessageType type);
        void setDataSize(size_t dataSize);
        void setBodyHash(int hash);

        UniqueId getSourceId() const;
        MessageType getMessageType() const;
        size_t getDataSize() const;
        int getBodyHash() const;
        int getHeaderHash() const;
        bool hasBody() const;

        void serialize(BinaryStream& bs) const;
        static Message deserialize(BinaryStream& bs);

        static const size_t Size = 5*sizeof(int);

    private:

        UniqueId m_sourceId;
        // auth
        MessageType m_type;
        size_t m_dataSize;
        int m_bodyHash;
        int m_headerHash;

    }; // Message class
} // BattleRoom namespace
#endif // MESSAGE_H

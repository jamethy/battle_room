#include "battle_room/networking/message.h"

namespace BattleRoom {

    Message::Message() :
        m_messageId(UniqueId::generateInvalidId()),
        m_type(MessageType::Invalid),
        m_dataSize(0)
    { }

    void Message::setMessageId(UniqueId id) {
        m_messageId = id;
    }

    void Message::setMessageType(MessageType type) {
        m_type = type;
    }

    void Message::setDataSize(size_t dataSize) {
        m_dataSize = dataSize;
    }


    UniqueId Message::getMessageId() const {
        return m_messageId;
    }

    MessageType Message::getMessageType() const {
        return m_type;
    }

    size_t Message::getDataSize() const {
        return m_dataSize;
    }

    bool Message::hasBody() const {
        return m_dataSize > 0;
    }

    void Message::serialize(BinaryStream& bs) const {
        m_messageId.serialize(bs);
        bs.writeInt((int)m_type);
        bs.writeInt((int)m_dataSize);
    }

    Message Message::deserialize(BinaryStream& bs) {
        Message msg;
        msg.setMessageId(UniqueId::deserialize(bs));
        msg.setMessageType((MessageType)bs.readInt());
        msg.setDataSize((size_t)bs.readInt());
        return msg;
    }

} // BattleRoom namespace

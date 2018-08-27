#include "message.h"

namespace BattleRoom {

    Message::Message() :
        m_sourceId(UniqueId::generateInvalidId()),
        m_type(MessageType::InvalidRequest),
        m_dataSize(0),
        m_bodyHash(0),
        m_headerHash(0)
    { }

    Message::Message(MessageType type) : Message()
    { 
        m_type = type;
    }

    int Message::hash() const {
        return m_sourceId.hash() + m_type + m_dataSize + m_bodyHash;
    }

    void Message::setSourceId(UniqueId id) {
        m_sourceId = id;
    }

    void Message::setMessageType(MessageType type) {
        m_type = type;
    }

    void Message::setDataSize(size_t dataSize) {
        m_dataSize = dataSize;
    }

    void Message::setBodyHash(int hash) {
        m_bodyHash = hash;
    }

    UniqueId Message::getSourceId() const {
        return m_sourceId;
    }

    MessageType Message::getMessageType() const {
        return m_type;
    }

    size_t Message::getDataSize() const {
        return m_dataSize;
    }

    int Message::getBodyHash() const {
        return m_bodyHash;
    }

    int Message::getHeaderHash() const {
        return m_headerHash;
    }

    bool Message::hasBody() const {
        return m_dataSize > 0;
    }

    void Message::serialize(BinaryStream& bs) const {
        m_sourceId.serialize(bs);
        bs.writeInt((int)m_type);
        bs.writeInt((int)m_dataSize);
        bs.writeInt(m_bodyHash);
        bs.writeInt(hash());
    }

    Message Message::deserialize(BinaryStream& bs) {
        Message msg;
        msg.setSourceId(UniqueId::deserialize(bs));
        msg.setMessageType((MessageType)bs.readInt());
        msg.setDataSize((size_t)bs.readInt());
        msg.setBodyHash(bs.readInt());
        msg.m_headerHash = bs.readInt();
        return msg;
    }

} // BattleRoom namespace

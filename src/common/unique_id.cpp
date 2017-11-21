#include "battle_room/common/unique_id.h"
#include "battle_room/common/string_utils.h"

namespace BattleRoom {

    UniqueId::UniqueId(int id)
            : m_id(id) {}

    UniqueId UniqueId::generateNewNetworkId() {
        static int current_id = 1;
        return UniqueId(++current_id);
    }

    UniqueId UniqueId::generateNewLocalId() {
        static int current_id = -1;
        return UniqueId(--current_id);
    }

    UniqueId UniqueId::generateInvalidId() {
        return UniqueId(0);
    }

    UniqueId UniqueId::fromString(std::string str) {
        return isNumber(str) ? UniqueId(stoll(str)) : generateInvalidId();
    }

    bool UniqueId::isValid() const {
        return m_id != 0;
    }

    std::string UniqueId::toString() const {
        return std::to_string(m_id);
    }

    bool UniqueId::operator==(const UniqueId &other) const {
        return m_id == other.m_id;
    }

    bool UniqueId::operator!=(const UniqueId &other) const {
        return !(*this == other);
    }

    bool UniqueId::operator<(const UniqueId &other) const {
        return m_id < other.m_id;
    }

    std::size_t UniqueId::hash() const {
        return std::hash<int>()(m_id);
    }

    void UniqueId::serialize(BinaryStream& bs) const {
        bs.writeInt(m_id);
    }
    UniqueId UniqueId::deserialize(BinaryStream& bs) {
        return UniqueId(bs.readInt());
    }

} // BattleRoom namespace

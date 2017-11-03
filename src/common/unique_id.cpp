#include "battle_room/common/unique_id.h"
#include "battle_room/common/string_utils.h"

namespace BattleRoom {

    UniqueId::UniqueId(long long id)
            : m_id(id) {}

    UniqueId UniqueId::generateNewNetworkId() {
        static long long current_id = 1;
        return UniqueId(++current_id);
    }

    UniqueId UniqueId::generateNewLocalId() {
        static long long current_id = -1;
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
        return std::hash<long long>()(m_id);
    }

} // BattleRoom namespace

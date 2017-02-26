#include "battle_room/common/unique_id.h"

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

    bool UniqueId::isValid() {
        return m_id != 0;
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

} // BattleRoom namespace

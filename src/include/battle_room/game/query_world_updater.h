#ifndef QUERY_WORLD_UPDATER_H
#define QUERY_WORLD_UPDATER_H

#include "battle_room/common/resource.h"
#include "battle_room/common/unique_id.h"

#include <memory>

namespace BattleRoom {

    class QueryWorldUpdater : public Resource {

    public:

        // destructor
        virtual ~QueryWorldUpdater() {}

        virtual void clientUpdate() {}

        const UniqueId getUniqueId() const {
            return m_uniqueId;
        }

    private:

        UniqueId m_uniqueId = UniqueId::generateNewLocalId();

    }; // QueryWorldUpdater

    typedef std::unique_ptr<QueryWorldUpdater> UniqueWorldUpdater;

} // BattleRoom namespace
#endif // QUERY_WORLD_UPDATER_H

#ifndef QUERY_WORLD_UPDATER_H
#define QUERY_WORLD_UPDATER_H

#include "battle_room/common/resource.h"
#include "battle_room/common/unique_id.h"
#include "battle_room/game/user.h"

#include <memory>

namespace BattleRoom {

    class QueryWorldUpdater : public Resource {

    public:

        // destructor
        virtual ~QueryWorldUpdater();

        virtual void clientUpdate();

        virtual void registerUser(User user);
        virtual void unregisterUser(UniqueId userId);

        const UniqueId getUniqueId() const;

        // inherited
        virtual void applySettings(ResourceDescriptor settings) override;

    private:

        UniqueId m_uniqueId = UniqueId::generateNewLocalId();

    }; // QueryWorldUpdater

    typedef std::unique_ptr<QueryWorldUpdater> UniqueWorldUpdater;

} // BattleRoom namespace
#endif // QUERY_WORLD_UPDATER_H

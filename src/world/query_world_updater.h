#ifndef BATTLE_ROOM_QUERY_WORLD_UPDATER_H
#define BATTLE_ROOM_QUERY_WORLD_UPDATER_H

#include "common/resource.h"
#include "common/unique_id.h"
#include "networking/user.h"

#include <memory>

namespace BattleRoom {

    /**
     * Base class for classes that will update a game world.
     *
     * Doesn't really update the world at all
     */
    class QueryWorldUpdater : public Resource {

    public:

        // destructor
        ~QueryWorldUpdater() override;

        virtual void clientUpdate();

        virtual bool start();

        virtual void registerUser(User user);

        virtual void unregisterUser(UniqueId userId);

        const UniqueId getUniqueId() const;

        // inherited
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    private:

        UniqueId m_uniqueId = UniqueId::generateNewLocalId();

    }; // QueryWorldUpdater

    typedef std::unique_ptr<QueryWorldUpdater> UniqueWorldUpdater;

} // BattleRoom namespace
#endif // BATTLE_ROOM_QUERY_WORLD_UPDATER_H

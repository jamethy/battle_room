#ifndef QUERY_WORLD_UPDATER_H
#define QUERY_WORLD_UPDATER_H

#include "resource.h"
#include "unique_id.h"
#include "user.h"

#include <memory>

namespace BattleRoom {

    class QueryWorldUpdater : public Resource {

    public:

        // destructor
        ~QueryWorldUpdater() override;

        virtual void clientUpdate();

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
#endif // QUERY_WORLD_UPDATER_H

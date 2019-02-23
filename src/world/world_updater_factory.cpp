#include "networking/laggy_server.h"
#include "world/world_updater_factory.h"
#include "world/local_world_updater.h"
#include "networking/sdl_client.h"
#include "networking/sdl_server.h"

namespace BattleRoom {

    UniqueWorldUpdater WorldUpdaterFactory::createWorldUpdater(ResourceDescriptor settings) {

        auto type = settings.getSubResource("Type").getValue();

        if (keyMatch("Local", type)) {
            return UniqueWorldUpdater(new LocalWorldUpdater(settings));

        } else if (keyMatch("Server", type)) {
            return UniqueWorldUpdater(new SdlServer(settings));

        } else if (keyMatch("LaggyServer", type)) {
            return UniqueWorldUpdater(new LaggyServer(settings));

        } else if (keyMatch("Client", type)) {
            return UniqueWorldUpdater(new SdlClient(settings));
        } else {
            return createEmptyUpdater();
        }
    }

    UniqueWorldUpdater WorldUpdaterFactory::createEmptyUpdater() {
        return UniqueWorldUpdater(new QueryWorldUpdater());
    }

} // BattleRoom namespace


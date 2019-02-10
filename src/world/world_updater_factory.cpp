#include "world/world_updater_factory.h"
#include "world/local_world_updater.h"
#include "networking/sdl_client.h"
#include "networking/sdl_server.h"

namespace BattleRoom {

    UniqueWorldUpdater WorldUpdaterFactory::createWorldUpdater(ResourceDescriptor settings) {

        if (keyMatch("Local", settings.getValue())) {
            return UniqueWorldUpdater(new LocalWorldUpdater(settings));

        } else if (keyMatch("Server", settings.getValue())) {
            return UniqueWorldUpdater(new SdlServer(settings));

        } else if (keyMatch("Client", settings.getValue())) {
            return UniqueWorldUpdater(new SdlClient(settings));
        } else {
            return createEmptyUpdater();
        }
    }

    UniqueWorldUpdater WorldUpdaterFactory::createEmptyUpdater() {
        return UniqueWorldUpdater(new QueryWorldUpdater());
    }

} // BattleRoom namespace


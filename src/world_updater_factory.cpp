#include "world_updater_factory.h"
#include "local_world_updater.h"
#include "./sdl_client.h"
#include "./sdl_server.h"

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


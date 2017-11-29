#include "battle_room/networking/world_updater_factory.h"
#include "battle_room/game/local_world_updater.h"
#include "./sdl_client.h"
#include "./sdl_server.h"

namespace BattleRoom {

///////////////////////////////////////////////////////////////////////////////////////////
// Empty World Updater
    class EmptyWorldUpdater : public QueryWorldUpdater {
    public:
        void applySettings(ResourceDescriptor settings) { (void) settings; /*unused*/ }
    }; // EmptyWorldUpdater class

///////////////////////////////////////////////////////////////////////////////////////////
// World Updater Factory

    UniqueWorldUpdater WorldUpdaterFactory::createWorldUpdater(ResourceDescriptor settings) {

        if (keyMatch("Local", settings.getValue())) {
            return UniqueWorldUpdater(new LocalWorldUpdater(settings));
        } else if (keyMatch("Server", settings.getValue())) {
            return UniqueWorldUpdater(new SdlServer(settings));
        } else if (keyMatch("Client", settings.getValue())) {
            return UniqueWorldUpdater(new SdlClient(settings));
        } else {
            return UniqueWorldUpdater(new EmptyWorldUpdater());
        }
    }

    UniqueWorldUpdater WorldUpdaterFactory::createEmptyUpdater() {
        return UniqueWorldUpdater(new EmptyWorldUpdater());
    }

} // BattleRoom namespace


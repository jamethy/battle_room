#include "battle_room/networking/world_updater_factory.h"
#include "battle_room/networking/network_world_updater.h"
#include "battle_room/game/local_world_updater.h"

namespace BattleRoom {

///////////////////////////////////////////////////////////////////////////////////////////
// Empty World Updater
class EmptyWorldUpdater : public QueryWorldUpdater {

public:
    
    ~EmptyWorldUpdater(){}
    void applySettings(ResourceDescriptor settings) { (void)settings; /*unused*/ }

}; // EmptyWorldUpdater class


///////////////////////////////////////////////////////////////////////////////////////////
// World Updater Factory

UniqueWorldUpdater WorldUpdaterFactory::createWorldUpdater(ResourceDescriptor settings) {

    if ( keyMatch("Local", settings.getValue()) ) {
        return UniqueWorldUpdater(new LocalWorldUpdater(settings));
    }
    else if ( keyMatch("Network", settings.getValue()) ) {
        return UniqueWorldUpdater(new NetworkWorldUpdater(settings));
    }
    else {
        return UniqueWorldUpdater(new EmptyWorldUpdater());
    }
}

UniqueWorldUpdater WorldUpdaterFactory::createEmptyUpdater() {
    return UniqueWorldUpdater(new EmptyWorldUpdater());
}

} // BattleRoom namespace


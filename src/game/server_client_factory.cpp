#include "battle_room/game/server_client_factory.h"

namespace BattleRoom {

UniqueServerClient ServerClientFactory::createServerClient(ResourceDescriptor settings) {

    return createEmptyServerClient();
}

UniqueServerClient ServerClientFactory::createEmptyServerClient() {
    return UniqueServerClient(nullptr);
}

} // BattleRoom namespace

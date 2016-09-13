#include "battle_room/networking/server_client_factory.h"
#include "battle_room/networking/local_server_client.h"
#include "battle_room/networking/remote_server_client.h"
#include "battle_room/networking/host_server_client.h"

using std::vector;

namespace BattleRoom {


////////////////////////////////////////////////////////////////////////////////
// Empty Server Client
class EmptyServerClient : public ServerClient {
public:
    void updateBuffer() {}
    vector<GameObject> getAllGameObjects() override { return vector<GameObject>(); }
    void applySettings(ResourceDescriptor settings) override { }
}; // EmptyServerClient class


UniqueServerClient ServerClientFactory::createServerClient(ResourceDescriptor settings) {
    
    if ( keyMatch("Local", settings.getValue()) ) {
        return UniqueServerClient(new LocalServerClient(settings));
    }
    else if ( keyMatch("Host", settings.getValue()) ) {
        return UniqueServerClient(new HostServerClient(settings));
    }
    else if ( keyMatch("Remote", settings.getValue()) ) {
        return UniqueServerClient(new RemoteServerClient(settings));
    }
    else {
        return createEmptyServerClient();
    }
}

UniqueServerClient ServerClientFactory::createEmptyServerClient() {
    return UniqueServerClient(new EmptyServerClient());
}

} // BattleRoom namespace

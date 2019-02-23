#ifndef BATTLE_ROOM_LAGGY_SERVER_H
#define BATTLE_ROOM_LAGGY_SERVER_H

#include "networking/sdl_server.h"

namespace BattleRoom {

    class LaggyServer : public SdlServer {

        // constructors
        explicit LaggyServer(ResourceDescriptor settings);

        void sendMessage(Message &message, BinaryStream &data, UniqueId clientId) override;

        void handleMessage(Message &message, BinaryStream &data, UniqueId clientId) override;

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    }; // LaggyServer class

} // BattleRoom namespace
#endif // BATTLE_ROOM_LAGGY_SERVER_H

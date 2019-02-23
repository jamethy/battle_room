#ifndef BATTLE_ROOM_LAGGY_CLIENT_H
#define BATTLE_ROOM_LAGGY_CLIENT_H

#include "sdl_client.h"

namespace BattleRoom {
    class LaggyClient : public SdlClient {
    public:

        // constructors
        explicit LaggyClient(ResourceDescriptor settings);

        void sendMessage(Message &message, BinaryStream &data) override;

        void handleMessage(Message &message, BinaryStream &data) override;

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    private:

        int m_simulatedLag; // ms
        
    }; // LaggyClient class
} // BattleRoom namespace
#endif //BATTLE_ROOM_LAGGY_CLIENT_H

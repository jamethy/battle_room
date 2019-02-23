#include "laggy_client.h"

namespace BattleRoom {

    LaggyClient::LaggyClient(ResourceDescriptor settings) : SdlClient(settings) {
        applySettings(settings);
    }

    void LaggyClient::sendMessage(Message &message, BinaryStream &data) {
        std::this_thread::sleep_for(std::chrono::milliseconds(m_simulatedLag));
        SdlClient::sendMessage(message, data);
    }

    void LaggyClient::handleMessage(Message &message, BinaryStream &data) {
        std::this_thread::sleep_for(std::chrono::milliseconds(m_simulatedLag));
        SdlClient::handleMessage(message, data);
    }

    void LaggyClient::applySettings(ResourceDescriptor settings) {
        SdlClient::applySettings(settings);
        ResourceDescriptor sub = settings.getSubResource("Lag");

        if (isNotEmpty(sub.getValue())) {
            m_simulatedLag = stoi(sub.getValue());
        }
    }

    ResourceDescriptor LaggyClient::getSettings() const {
        auto rd = SdlClient::getSettings();
        rd.emplaceSubResource("Lag", std::to_string(m_simulatedLag));
        return rd;
    }
} // BattleRoom namespace

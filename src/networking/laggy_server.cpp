#include "laggy_server.h"

namespace BattleRoom {

    LaggyServer::LaggyServer(ResourceDescriptor settings) : SdlServer(settings) {
        applySettings(settings);
    }

    void LaggyServer::sendMessage(Message &message, BinaryStream &data,
                                  UniqueId clientId) {
        std::this_thread::sleep_for(std::chrono::milliseconds(m_simulatedLag));
        SdlServer::sendMessage(message, data, clientId);
    }

    void LaggyServer::handleMessage(Message &message, BinaryStream &data,
                                    UniqueId clientId) {
        std::this_thread::sleep_for(std::chrono::milliseconds(m_simulatedLag));
        ServerConnection::handleMessage(message, data, clientId);
    }

    void LaggyServer::applySettings(ResourceDescriptor settings) {
        SdlServer::applySettings(settings);

        ResourceDescriptor sub = settings.getSubResource("Lag");

        if (isNotEmpty(sub.getValue())) {
            m_simulatedLag = stoi(sub.getValue());
        }
    }

    ResourceDescriptor LaggyServer::getSettings() const {
        auto rd = SdlServer::getSettings();
        rd.emplaceSubResource("Lag", std::to_string(m_simulatedLag));
        return rd;
    }
} // BattleRoom namespace

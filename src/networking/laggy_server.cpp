#include "networking/laggy_server.h"

#include "laggy_server.h"

namespace BattleRoom {

    LaggyServer::LaggyServer(ResourceDescriptor settings) : SdlServer(settings) {

    }

    void LaggyServer::sendMessage(Message &message, BinaryStream &data,
                                  UniqueId clientId) {
        SdlServer::sendMessage(message, data, clientId);
    }

    void LaggyServer::handleMessage(Message &message, BinaryStream &data,
                                    UniqueId clientId) {
        ServerConnection::handleMessage(message, data, clientId);
    }

    void LaggyServer::applySettings(ResourceDescriptor settings) {
        SdlServer::applySettings(settings);
    }

    ResourceDescriptor LaggyServer::getSettings() const {
        return SdlServer::getSettings();
    }
} // BattleRoom namespace

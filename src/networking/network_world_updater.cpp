#include "battle_room/networking/network_world_updater.h"
#include "battle_room/networking/client_connection.h"
#include "battle_room/game/query_world.h"
#include "battle_room/game/command_receiver.h"

#include <chrono>
#include <iostream>

namespace BattleRoom {

    // apply settings
    void NetworkWorldUpdater::applySettings(ResourceDescriptor settings) {
        (void)settings;
    }

    void sendCommandsToServer(BinaryStream& commandStream) {

        const auto commands = CommandReceiver::getAndClearCommands();

        if (commands.size() > 0) {

            commandStream.reset();
            commandStream.writeInt(commands.size());

            for (const auto& cmd : commands) {
                cmd.serialize(commandStream);
            }

            Message msg;
            msg.setMessageType(MessageType::PostCommandsRequest);

            ClientConnection::send(msg, commandStream);
        }
    }

    void worldUpdaterFunction(bool &keepUpdating) {

        Message worldUpdateRequest;
        worldUpdateRequest.setMessageType(MessageType::GetWorldRequest);

        BinaryStream commandStream(1000);

        while (keepUpdating) {

            sendCommandsToServer(commandStream);
            
            // request world update
            ClientConnection::send(worldUpdateRequest);

            // fake load
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

// constructors
    NetworkWorldUpdater::NetworkWorldUpdater(ResourceDescriptor settings)
            : m_keepUpdating(true) {
        applySettings(settings);

        m_worldThread = std::thread(worldUpdaterFunction, std::ref(m_keepUpdating)
        );
    }

    NetworkWorldUpdater::~NetworkWorldUpdater() {
        m_keepUpdating = false; //TODO make this an atomic boolean
        if (m_worldThread.joinable()) {
            m_worldThread.join();
        }

        // close network connections?
    }

} // BattleRoom namespace

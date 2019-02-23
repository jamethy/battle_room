#include "networking/client_connection.h"
#include "world/query_world.h"
#include "world/command_receiver.h"

namespace BattleRoom {
    void worldUpdaterFunction(LocalUpdatingWorld &world, bool &keepUpdating, std::mutex &worldMutex) {

        while (keepUpdating) {
            worldMutex.lock();
            world.update();
            worldMutex.unlock();
            QueryWorld::updateCopyWorld(world);
//            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    ClientConnection::ClientConnection() :
            m_commandStream(BinaryStream(400)) {}

    bool ClientConnection::start() {
        if (!m_keepUpdating) {
            m_keepUpdating = true;
            m_worldThread = std::thread(worldUpdaterFunction,
                                        std::ref(m_world),
                                        std::ref(m_keepUpdating),
                                        std::ref(m_worldMutex)
            );
        }
        return true;
    }

    ClientConnection::~ClientConnection() {
        m_keepUpdating = false; //TODO make this an atomic boolean
        if (m_worldThread.joinable()) {
            m_worldThread.join();
        }
    }


    void ClientConnection::handleMessage(Message &message, BinaryStream &body) {

        MessageType requestType = message.getMessageType();

        if (MessageType::GetWorldResponse == requestType) {

            m_worldMutex.lock();
            m_world.copy(World::deserialize(body));
            m_worldMutex.unlock();

        } else if (MessageType::RegisterUserResponse == requestType) {
            User user = User::deserialize(body);
            QueryWorld::setClientId(user.getUniqueId());
        }

    }

    void ClientConnection::clientUpdate() {

        const auto commands = CommandReceiver::getAndClearCommands();

        if (!commands.empty()) {

            m_commandStream.reset();
            m_commandStream.writeInt(static_cast<int>(commands.size()));

            for (const auto &cmd : commands) {
                cmd.serialize(m_commandStream);
            }

            Message msg;
            msg.setMessageType(MessageType::PostCommandsRequest);

            sendMessage(msg, m_commandStream);
        }
    }

    void ClientConnection::registerUser(User user) {
        Message message(MessageType::RegisterUserRequest);
        m_commandStream.reset();
        user.serialize(m_commandStream);
        sendMessage(message, m_commandStream);
    }

    void ClientConnection::applySettings(ResourceDescriptor settings) {
        QueryWorldUpdater::applySettings(settings);
    }

    ResourceDescriptor ClientConnection::getSettings() const {
        auto rd = QueryWorldUpdater::getSettings();
        rd.setValue("Client");
        return rd;
    }

} // BattleRoom namespace

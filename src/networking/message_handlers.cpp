#include "battle_room/networking/message.h"

namespace BattleRoom {

    void handleGeWorld(BinaryStream& bs) {
    }

    void handlePostCommand(BinaryStream& bs) {
    }

    void Message::handle(BinaryStream& bs) {
        switch (m_type) {
            case GetWorld:
                handleGeWorld(bs);
                break;
            case PostCommand:
                break;
            default:
                // unrecognized
                break;
        }
    }

} // BattleRoom namespace

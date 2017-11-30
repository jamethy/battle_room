#include "battle_room/game/command.h"

namespace BattleRoom {

    Command::Command() : 
        m_type(CommandType::Invalid), 
        m_target(UniqueId::generateInvalidId()), 
        m_commander(UniqueId::generateInvalidId()), 
        m_point(Vector2D()) {}

    Command::Command(CommandType type, UniqueId target, UniqueId commander, Vector2D point)
        : m_type(type), m_target(target), m_commander(commander), m_point(point) {}

    // getters and setters
    CommandType Command::getType() const {
        return m_type;
    }

    UniqueId Command::getTarget() const {
        return m_target;
    }

    UniqueId Command::getCommander() const {
        return m_commander;
    }

    Vector2D Command::getPoint() const {
        return m_point;
    }


    void Command::setType(CommandType type) {
        m_type = type;
    }

    void Command::setTarget(UniqueId target) {
        m_target = target;
    }

    void Command::setCommander(UniqueId commander) {
        m_commander = commander;
    }

    void Command::setPoint(Vector2D point) {
        m_point = point;
    }

    void Command::serialize(BinaryStream& bs) const {
        bs.writeInt((int)m_type);
        m_target.serialize(bs);
        m_commander.serialize(bs);
        m_point.serialize(bs);
    }

    Command Command::deserialize(BinaryStream& bs) {
        Command cmd;
        cmd.m_type = (CommandType)bs.readInt();
        cmd.m_target = UniqueId::deserialize(bs);
        cmd.m_commander = UniqueId::deserialize(bs);
        cmd.m_point = Vector2D::deserialize(bs);
        return cmd;
    }

} // BattleRoom namespace

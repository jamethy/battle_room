#include "battle_room/game/command.h"

namespace BattleRoom {

    Command::Command() : 
        m_type(CommandType::Invalid), 
        m_target(UniqueId::generateInvalidId()), 
        m_point(Vector2D()) {}

    Command::Command(CommandType type, UniqueId target, Vector2D point)
        : m_type(type), m_target(target), m_point(point) {}

    // getters and setters
    CommandType Command::getType() const {
        return m_type;
    }

    UniqueId Command::getTarget() const {
        return m_target;
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

    void Command::setPoint(Vector2D point) {
        m_point = point;
    }
} // BattleRoom namespace

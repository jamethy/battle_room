#ifndef COMMAND_H
#define COMMAND_H

#include "battle_room/common/unique_id.h"
#include "battle_room/common/vector2d.h"
#include "battle_room/game/command_type.h"

namespace BattleRoom {

    class Command {

        public:

            // constructors
            Command();
            Command(CommandType type, UniqueId target, Vector2D point);

            // getters and setters
            CommandType getType() const;
            UniqueId getTarget() const;
            Vector2D getPoint() const;

            void setType(CommandType type);
            void setTarget(UniqueId target);
            void setPoint(Vector2D point);

            void serialize(BinaryStream& bs) const;
            static Command deserialize(BinaryStream& bs);

        private:

            CommandType m_type;
            UniqueId m_target;
            Vector2D m_point;

    }; // Command class
} // BattleRoom namespace
#endif // COMMAND_H

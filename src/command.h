#ifndef COMMAND_H
#define COMMAND_H

#include "unique_id.h"
#include "vector2d.h"
#include "command_type.h"

namespace BattleRoom {

    class Command {

        public:

            // constructors
            Command();
            Command(CommandType type, UniqueId target, UniqueId commander, Vector2D point);

            // getters and setters
            CommandType getType() const;
            UniqueId getTarget() const;
            UniqueId getCommander() const;
            Vector2D getPoint() const;

            void setType(CommandType type);
            void setTarget(UniqueId target);
            void setCommander(UniqueId commander);
            void setPoint(Vector2D point);

            void serialize(BinaryStream& bs) const;
            static Command deserialize(BinaryStream& bs);

        private:

            CommandType m_type;
            UniqueId m_target;
            UniqueId m_commander;
            Vector2D m_point;

    }; // Command class
} // BattleRoom namespace
#endif // COMMAND_H
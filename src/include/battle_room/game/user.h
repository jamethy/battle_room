#ifndef BATTLE_ROOM_USER_H
#define BATTLE_ROOM_USER_H

#include "battle_room/common/resource.h"
#include "battle_room/common/unique_id.h"
#include "battle_room/common/binary_stream.h"

namespace BattleRoom {

    class User : public Resource {

        public:

            User();

            // setters and getters
            void setUniqueId(UniqueId id);
            void setName(std::string name);

            UniqueId getUniqueId() const;
            std::string getName() const;

            void serialize(BinaryStream& bs) const;
            static User deserialize(BinaryStream& bs);

            // inherited
            void applySettings(ResourceDescriptor settings) override;

        private:

            UniqueId m_uniqueId;
            std::string m_name;

    }; // User
} // BattleRoom namespace
#endif // BATTLE_ROOM_USER_H


#ifndef BATTLE_ROOM_USER_H
#define BATTLE_ROOM_USER_H

#include "common/resource.h"
#include "common/unique_id.h"
#include "common/binary_stream.h"

namespace BattleRoom {

    class User : public Resource {

    public:

        User();

        explicit User(ResourceDescriptor settings);

        // setters and getters
        void setUniqueId(UniqueId id);

        void setName(std::string name);

        UniqueId getUniqueId() const;

        std::string getName() const;

        void serialize(BinaryStream &bs) const;

        static User deserialize(BinaryStream &bs);

        // inherited
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    private:

        UniqueId m_uniqueId;
        std::string m_name;

    }; // User
} // BattleRoom namespace
#endif // BATTLE_ROOM_USER_H


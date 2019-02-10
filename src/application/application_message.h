#ifndef BATTLE_ROOM_APPLICATION_MESSAGE_H
#define BATTLE_ROOM_APPLICATION_MESSAGE_H

#include "common/resource.h"
#include "common/unique_id.h"

namespace BattleRoom {

    class ApplicationMessage {

        public:

            enum Type { Add, Modify, Remove, Quit };
            ApplicationMessage();
            ApplicationMessage(Type type, UniqueId target, ResourceDescriptor settings);
            static ApplicationMessage add(ResourceDescriptor settings);
            static ApplicationMessage modify(UniqueId target, ResourceDescriptor settings);
            static ApplicationMessage remove(UniqueId target);
            static ApplicationMessage quit();

            Type getType();
            UniqueId getTarget();
            ResourceDescriptor getSettings();

        private:

            Type m_type;
            UniqueId m_target;
            ResourceDescriptor m_settings;

    }; // ApplicationMessage class
} // BattleRoom namespace
#endif // BATTLE_ROOM_APPLICATION_MESSAGE_H

#ifndef APPLICATION_MESSAGE_H
#define APPLICATION_MESSAGE_H

#include "battle_room/common/resource.h"
#include "battle_room/common/unique_id.h"

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
#endif // APPLICATION_MESSAGE_H

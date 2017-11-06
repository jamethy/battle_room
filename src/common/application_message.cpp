
#include "battle_room/common/application_message.h"

namespace BattleRoom {
    ApplicationMessage::ApplicationMessage() :
        m_type(Type::Remove), m_target(UniqueId::generateInvalidId()) {}

    ApplicationMessage::ApplicationMessage(Type type, UniqueId target, ResourceDescriptor settings) :
        m_type(type), m_target(target), m_settings(settings) {}

    ApplicationMessage ApplicationMessage::add(ResourceDescriptor settings) {
        return ApplicationMessage(Type::Add, UniqueId::generateInvalidId(), settings);
    }

    ApplicationMessage ApplicationMessage::modify(UniqueId target, ResourceDescriptor settings) {
        return ApplicationMessage(Type::Modify, target, settings);
    }

    ApplicationMessage ApplicationMessage::remove(UniqueId target) {
        return ApplicationMessage(Type::Remove, target, ResourceDescriptor());
    }

    ApplicationMessage::Type ApplicationMessage::getType() {
        return m_type;
    }

    UniqueId ApplicationMessage::getTarget() {
        return m_target;
    }

    ResourceDescriptor ApplicationMessage::getSettings() {
        return m_settings;
    }


} // BattleRoom namespace

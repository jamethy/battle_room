#include "application/application_message.h"

namespace BattleRoom {
    ApplicationMessage::ApplicationMessage() :
        m_type(Type::Remove), m_target(UniqueId::generateInvalidId()) {}

    ApplicationMessage::ApplicationMessage(Type type, UniqueId target, ResourceDescriptor settings) :
        m_type(type), m_target(target), m_settings(std::move(settings)) {}

    ApplicationMessage ApplicationMessage::add(ResourceDescriptor settings) {
        return ApplicationMessage(Type::Add, UniqueId::generateInvalidId(), std::move(settings));
    }

    ApplicationMessage ApplicationMessage::modify(UniqueId target, ResourceDescriptor settings) {
        return ApplicationMessage(Type::Modify, target, std::move(settings));
    }

    ApplicationMessage ApplicationMessage::remove(UniqueId target) {
        return ApplicationMessage(Type::Remove, target, ResourceDescriptor());
    }

    ApplicationMessage ApplicationMessage::quit() {
        return ApplicationMessage(Type::Quit, UniqueId::generateInvalidId(), ResourceDescriptor());
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

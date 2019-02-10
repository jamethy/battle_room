#include "networking/user.h"

namespace BattleRoom {

    void User::applySettings(ResourceDescriptor settings) {
        if (isNotEmpty(settings.getValue())) {
            m_name = settings.getValue();
        }
    }

    ResourceDescriptor User::getSettings() const {
        ResourceDescriptor rd("User", m_name);
        std::vector<ResourceDescriptor> subs = {};
        subs.emplace_back("UniqueId", m_uniqueId.toString());
        rd.setSubResources(subs);
        return rd;
    }


    User::User() :
        m_uniqueId(UniqueId::generateNewLocalId()),
        m_name("name")
    { }

    User::User(ResourceDescriptor settings) : User() 
    {
        applySettings(std::move(settings));
    }

    UniqueId User::getUniqueId() const {
        return m_uniqueId;
    }

    void User::setUniqueId(UniqueId id) {
        m_uniqueId = id;
    }

    std::string User::getName() const {
        return m_name;
    }

    void User::setName(std::string name) {
        m_name = name;
    }

    void User::serialize(BinaryStream& bs) const {
        m_uniqueId.serialize(bs);
        bs.writeString(m_name);
    }

    User User::deserialize(BinaryStream& bs) {
        User user;
        user.m_uniqueId = UniqueId::deserialize(bs);
        user.m_name = bs.readString();
        return user;
    }
} // BattleRoom namespace

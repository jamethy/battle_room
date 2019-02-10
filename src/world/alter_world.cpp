#include "world/alter_world.h"

namespace BattleRoom {

    static std::vector<UniqueGameObject> m_objectsToAdd;

    void AlterWorld::addObject(UniqueGameObject object) {
        m_objectsToAdd.push_back(std::move(object));
    }

    void AlterWorld::update(LocalUpdatingWorld& world) {

        for (auto& addedObj : m_objectsToAdd) {
            world.m_gameObjects.push_back(std::move(addedObj));
        }
        m_objectsToAdd.clear();
    }

} // BattleRoom namespace

#include "battle_room/game/world.h"

#include "battle_room/common/unique_id.h"
#include "battle_room/common/animation_handler.h"
#include "battle_room/game/objects/object_factory.h"

using std::vector;

namespace BattleRoom {

// apply settings

    void World::applySettings(ResourceDescriptor settings) {

        for (ResourceDescriptor &objDesc : settings.getSubResources("Background")) {
            DrawableObject* obj = new DrawableObject();
            obj->applySettings(objDesc);
            m_backgroundObjects.push_back(UniqueDrawableObject(obj));
        }

        ResourceDescriptor sub = settings.getSubResource("Time");
        if (isNotEmpty(sub.getValue())) {
            m_gameTime = toSeconds(sub.getValue());
        }

        m_gameObjects = ObjectFactory::getGameObjects(settings);
    }

// constructors
    World::World() {
        m_gameObjects.clear();
        m_backgroundObjects.clear();
    }

    World World::clone() const {
        World world;
        world.m_gameObjects = std::vector<UniqueGameObject>(m_gameObjects.size());
        world.m_gameObjects.clear();
        for (const auto& obj : m_gameObjects) {
            world.m_gameObjects.push_back(UniqueGameObject(obj->clone()));
        }
        world.m_backgroundObjects = std::vector<UniqueDrawableObject>(m_backgroundObjects.size());
        world.m_backgroundObjects.clear();
        for (const auto& obj : m_backgroundObjects) {
            world.m_backgroundObjects.push_back(UniqueDrawableObject(new DrawableObject(*obj)));
        }

        return world;
    }

    World::World(ResourceDescriptor settings)
            : World() {
        applySettings(settings);
    }

    const vector<UniqueGameObject>& World::getAllGameObjects() const {
        return m_gameObjects;
    }

    const GameObject* World::getGameObject(UniqueId id) const {
        for (const auto& obj : m_gameObjects) {
            if (obj->getUniqueId() == id) {
                return obj.get();
            }
        }
        return nullptr;
    }

    const vector<UniqueDrawableObject>& World::getBackgroundObjects() const {
        return m_backgroundObjects;
    }

    bool objectBoundaryContains(GameObject* obj, Vector2D point) {

        Vector2D relP = point
            .minus(obj->getPosition())
            .getRotated(obj->getRotation());

        return obj->getAnimation()
            .getFrame(obj->getAnimationState())
            .getBoundarySet()
            .contains(relP);
    }


    const GameObject* World::findIntersectingObject(Vector2D point) const {
        for (const auto& obj : m_gameObjects) {
            if (objectBoundaryContains(obj.get(), point)) {
                return obj.get(); 
            }
        }
        return nullptr;
    }

    seconds World::getGameTime() const {
        return m_gameTime;
    }

    void World::serialize(BinaryStream& bs) const {
        bs.writeSeconds(m_gameTime);
        bs.writeInt(m_backgroundObjects.size());
        for (const auto& obj : m_backgroundObjects) {
            obj->serialize(bs);
        }
        bs.writeInt(m_gameObjects.size());
        for (const auto& obj : m_gameObjects) {
            obj->serialize(bs);
        }
    }

    World World::deserialize(BinaryStream& bs) {
        World world;
        world.m_gameTime = bs.readSeconds();

        int numBackgrounds = bs.readInt();
        world.m_backgroundObjects = vector<UniqueDrawableObject>(numBackgrounds);;
        for (int i = 0; i < numBackgrounds; ++i) {
            world.m_backgroundObjects[i] = UniqueDrawableObject(new DrawableObject(DrawableObject::deserialize(bs)));
        }

        int numGameObjects = bs.readInt();
        world.m_gameObjects = vector<UniqueGameObject>(numGameObjects);
        for (int i = 0; i < numGameObjects; ++i) {
            world.m_gameObjects[i] = ObjectFactory::deserializeObject(bs);
        }

        return world;
    }

} // BattleRoom namespace

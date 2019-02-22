#include "world/world.h"
#include "common/unique_id.h"
#include "animation/animation_handler.h"
#include "world/object_factory.h"

#include <algorithm>

using std::vector;

namespace BattleRoom {

    // apply settings

    void World::applySettings(ResourceDescriptor settings) {

        for (ResourceDescriptor &objDesc : settings.getSubResources("Background")) {
            auto *obj = new DrawableObject();
            obj->applySettings(objDesc);
            m_backgroundObjects.push_back(UniqueDrawableObject(obj));
        }

        ResourceDescriptor sub = settings.getSubResource("Time");
        if (isNotEmpty(sub.getValue())) {
            m_gameTime = toSeconds(sub.getValue());
        }

        auto objects = ObjectFactory::getGameObjects(settings.getSubResource("Objects"));
        std::move(objects.begin(), objects.end(), std::back_inserter(m_gameObjects));
    }

    ResourceDescriptor World::getSettings() const {
        ResourceDescriptor rd("World", "");
        std::vector<ResourceDescriptor> subs = {};

        for (const auto &obj : m_backgroundObjects) {
            ResourceDescriptor sub = obj->getSettings();
            sub.setKey("Background");
            subs.push_back(sub);
        }

        subs.emplace_back("Time", std::to_string(m_gameTime));

        for (const auto &obj : m_gameObjects) {
            subs.push_back(obj->getSettings());
        }

        rd.setSubResources(subs);
        return rd;
    }

    // constructors
    World::World() :
            m_gameTime(0.0) {
        m_gameObjects.clear();
        m_backgroundObjects.clear();
    }

    World World::clone() const {
        World world;
        world.m_gameTime = m_gameTime;

        world.m_gameObjects = std::vector<UniqueGameObject>(m_gameObjects.size());
        world.m_gameObjects.clear();
        for (const auto &obj : m_gameObjects) {
            world.m_gameObjects.push_back(UniqueGameObject(obj->clone()));
        }
        world.m_backgroundObjects = std::vector<UniqueDrawableObject>(m_backgroundObjects.size());
        world.m_backgroundObjects.clear();
        for (const auto &obj : m_backgroundObjects) {
            world.m_backgroundObjects.push_back(UniqueDrawableObject(new DrawableObject(*obj)));
        }

        return world;
    }

    World::World(ResourceDescriptor settings)
            : World() {
        applySettings(std::move(settings));
    }

    const vector<UniqueGameObject> &World::getAllGameObjects() const {
        return m_gameObjects;
    }

    const GameObject *World::getGameObject(UniqueId id) const {
        for (const auto &obj : m_gameObjects) {
            if (obj->getUniqueId() == id) {
                return obj.get();
            }
        }
        return nullptr;
    }

    const vector<UniqueDrawableObject> &World::getBackgroundObjects() const {
        return m_backgroundObjects;
    }

    bool objectBoundaryContains(GameObject *obj, const Vector2D &point) {

        Vector2D relP = point
                .minus(obj->getPosition())
                .getRotated(obj->getRotation());

        return obj->getAnimation()
                .getFrame(obj->getAnimationState())
                .getBoundarySet()
                .contains(relP);
    }


    const GameObject *World::findIntersectingObject(Vector2D point) const {
        for (const auto &obj : m_gameObjects) {
            if (objectBoundaryContains(obj.get(), point)) {
                return obj.get();
            }
        }
        return nullptr;
    }

    seconds World::getGameTime() const {
        return m_gameTime;
    }

    void World::serialize(BinaryStream &bs) const {
        bs.writeSeconds(m_gameTime);
        bs.writeInt(static_cast<int>(m_backgroundObjects.size()));
        for (const auto &obj : m_backgroundObjects) {
            obj->serialize(bs);
        }
        bs.writeInt(static_cast<int>(m_gameObjects.size()));
        for (const auto &obj : m_gameObjects) {
            obj->serialize(bs);
        }
    }

    World World::deserialize(BinaryStream &bs) {
        World world;
        world.m_gameTime = bs.readSeconds();

        int numBackgrounds = bs.readInt();
        world.m_backgroundObjects = vector<UniqueDrawableObject>(static_cast<unsigned long>(numBackgrounds));;
        for (int i = 0; i < numBackgrounds; ++i) {
            world.m_backgroundObjects[i] = UniqueDrawableObject(new DrawableObject(DrawableObject::deserialize(bs)));
        }

        int numGameObjects = bs.readInt();
        world.m_gameObjects = vector<UniqueGameObject>(static_cast<unsigned long>(numGameObjects));
        for (int i = 0; i < numGameObjects; ++i) {
            world.m_gameObjects[i] = ObjectFactory::deserializeObject(bs);
        }

        return world;
    }

} // BattleRoom namespace

#include "battle_room/game/world.h"

#include "battle_room/common/unique_id.h"
#include "battle_room/common/animation_handler.h"
#include "battle_room/game/objects/object_factory.h"

using std::vector;

namespace BattleRoom {

// apply settings

    void World::applySettings(ResourceDescriptor settings) {

        for (ResourceDescriptor &objDesc : settings.getSubResources("Background")) {
            DrawableObject *obj = new DrawableObject();
            obj->applySettings(objDesc);
            m_backgroundObjects.push_back(obj);
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

    World::World(const World& other)
            : m_gameTime(other.m_gameTime)
    {
        m_gameObjects.clear();
        for (GameObject* obj : other.m_gameObjects) {
            m_gameObjects.push_back(obj->clone());
        }
        m_backgroundObjects.clear();
        for (DrawableObject* obj : other.m_backgroundObjects) {
            m_backgroundObjects.push_back(new DrawableObject(*obj));
        }
    }

    World::World(ResourceDescriptor settings)
            : World() {
        applySettings(settings);
    }

    void World::serialize(BinaryStream& bs) const {
        bs.writeDouble(m_gameTime);
    }

    World World::deserialize(BinaryStream& bs) {
        World world;
        world.m_gameTime = bs.readDouble();
        return world;
            //std::vector<GameObject *> m_gameObjects; // walls, stars, etc
            ////std::vector<DrawableObject *> m_backgroundObjects; // background
    }

    vector<GameObject *> World::getAllGameObjects() {
        return m_gameObjects;
    }

    GameObject* World::getGameObject(UniqueId id) {
        for (GameObject* obj : m_gameObjects) {
            if (obj->getUniqueId() == id) {
                return obj;
            }
        }
        return nullptr;
    }

    vector<DrawableObject *> World::getBackgroundObjects() {
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


    GameObject* World::findIntersectingObject(Vector2D point) {
        for (GameObject* obj : m_gameObjects) {
            if (objectBoundaryContains(obj, point)) {
                return obj; 
            }
        }
        return nullptr;
    }

    seconds World::getGameTime() {
        return m_gameTime;
    }

} // BattleRoom namespace

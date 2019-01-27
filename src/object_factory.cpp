#include "object_factory.h"
#include "player.h"
#include "bullet.h"
#include "ball.h"
#include "logger.h"

#include <map>

namespace BattleRoom {

    std::map<ObjectType, ResourceDescriptor> OBJECT_TEMPLATES = {
            {ObjectType::Player, ResourceDescriptor("Player", "")},
            {ObjectType::Bullet, ResourceDescriptor("Bullet", "")},
            {ObjectType::Ball,   ResourceDescriptor("Ball", "")},
            {ObjectType::None,   ResourceDescriptor("Object", "")}
    };

    ObjectType keyToType(const std::string &key) {
        if (keyMatch(key, "Player")) {
            return ObjectType::Player;
        } else if (keyMatch(key, "Bullet")) {
            return ObjectType::Bullet;
        } else if (keyMatch(key, "Ball")) {
            return ObjectType::Ball;
        } else {
            return ObjectType::None;
        }
    }

    std::string typeToKey(const ObjectType &type) {
        switch (type) {
            case ObjectType::None:
                return "None";
            case ObjectType::Ball:
                return "Ball";
            case ObjectType::Wall:
                return "Wall";
            case ObjectType::Bullet:
                return "Bullet";
            case ObjectType::Player:
                return "Player";
            default:
                Log::error("Unknown object type to key: ", (int) type);
                return "None";
        }
    }

    void ObjectFactory::applySettings(ResourceDescriptor settings) {

        for (const ResourceDescriptor &sub : settings.getSubResources()) {
            ObjectType type = keyToType(sub.getKey());
            OBJECT_TEMPLATES.at(type) = sub;
            Log::info("Read in object template for " + sub.getKey() + " to " + typeToKey(type));
        }
    }

    UniqueGameObject createTemplateObject(ResourceDescriptor settings) {

        GameObject *obj = nullptr;

        if (keyMatch("Player", settings.getKey())) {
            obj = new Player(UniqueId::generateNewNetworkId());
        } else if (keyMatch("Bullet", settings.getKey())) {
            obj = new Bullet(UniqueId::generateNewNetworkId());
        } else if (keyMatch("Ball", settings.getKey())) {
            obj = new Ball(UniqueId::generateNewNetworkId());
        } else {
            obj = new GameObject(UniqueId::generateNewNetworkId(), ObjectType::None);
        }

        obj->applySettings(settings);
        return UniqueGameObject(obj);
    }

    std::vector<UniqueGameObject> ObjectFactory::getGameObjects(ResourceDescriptor settings) {
        std::vector<UniqueGameObject> objects;

        for (const auto &objTemplate : OBJECT_TEMPLATES) {
            for (const ResourceDescriptor &objDesc : settings.getSubResources(objTemplate.second.getKey())) {
                auto obj = createTemplateObject(objTemplate.second);
                obj->applySettings(objDesc);
                objects.push_back(std::move(obj));
            }
        }
        return objects;
    }

    UniqueGameObject ObjectFactory::createObjectOfDescription(ResourceDescriptor settings) {

        const ObjectType type = keyToType(settings.getKey());
        UniqueGameObject obj = createObjectOfType(type);
        obj->applySettings(settings);
        return obj;
    }

    UniqueGameObject ObjectFactory::createObjectOfType(ObjectType type) {
        auto objectTeplate = OBJECT_TEMPLATES.find(type);
        if (objectTeplate != OBJECT_TEMPLATES.end()) {
            return createTemplateObject(objectTeplate->second);
        } else {
            return createObjectOfType(ObjectType::None);
        }
    }

    UniqueGameObject ObjectFactory::deserializeObject(BinaryStream &bs) {
        const ObjectType type = (ObjectType) bs.peekInt();
        switch (type) {
            case ObjectType::Ball:
                return UniqueGameObject(new Ball(Ball::deserialize(bs)));
            case ObjectType::Bullet:
                return UniqueGameObject(new Bullet(Bullet::deserialize(bs)));
            case ObjectType::Player:
                return UniqueGameObject(new Player(Player::deserialize(bs)));
            case ObjectType::Wall:
            case ObjectType::None:
            default:
                return UniqueGameObject(new GameObject(GameObject::deserialize(bs)));
        }
    }

    ResourceDescriptor ObjectFactory::getSettings() {
        ResourceDescriptor rd("ObjectTemplates", "");
        std::vector<ResourceDescriptor> subs = {};

        rd.setSubResources(subs);
        return rd;
    }

} // BattleRoom namespace

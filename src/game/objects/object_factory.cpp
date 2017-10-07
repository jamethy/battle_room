#include "battle_room/game/objects/object_factory.h"
#include "battle_room/game/objects/player.h"
#include "battle_room/game/objects/bullet.h"
#include "battle_room/game/objects/ball.h"

#include <map>

namespace BattleRoom {

    const std::map<ObjectType, ResourceDescriptor> OBJECT_TEMPLATES = {
        { ObjectType::Player, ResourceDescriptor("Player", "") },
        { ObjectType::Bullet, ResourceDescriptor("Bullet", "") },
        { ObjectType::Ball, ResourceDescriptor("Ball", "") },
        { ObjectType::None, ResourceDescriptor("Object", "") }
    };

    ObjectType keyToType(const std::string& key) {
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

    GameObject* createTemplateObject(ResourceDescriptor settings) {

        GameObject* obj = nullptr;

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
        return obj;
    }


    std::vector<GameObject*> ObjectFactory::getGameObjects(ResourceDescriptor settings) {
        std::vector<GameObject*> objects;

        for (const auto& objTemplate : OBJECT_TEMPLATES) {
            for (const ResourceDescriptor& objDesc : settings.getSubResources(objTemplate.second.getKey())) {
                GameObject* obj = createTemplateObject(objTemplate.second);
                obj->applySettings(objDesc);
                objects.push_back(obj);
            }
        }
        return objects;
    }

    GameObject* ObjectFactory::createObjectOfDescription(ResourceDescriptor settings) {

        const ObjectType type = keyToType(settings.getKey());
        GameObject* obj =  createObjectOfType(type);
        obj->applySettings(settings);
        return obj;
    }

    GameObject* ObjectFactory::createObjectOfType(ObjectType type) {
        auto objectTeplate = OBJECT_TEMPLATES.find(type);
        if (objectTeplate != OBJECT_TEMPLATES.end()) {
            return createTemplateObject(objectTeplate->second);
        } else {
            return createObjectOfType(ObjectType::None);
        }
    }

} // BattleRoom namespace
#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include "battle_room/game/game_object.h"

namespace BattleRoom {

/**
 * Static class for creating Objects
 */
    class ObjectFactory {

    public:

        static std::vector<GameObject*> getGameObjects(ResourceDescriptor settings);

        static GameObject* createObjectOfDescription(ResourceDescriptor settings);

        static GameObject* createObjectOfType(ObjectType type);

        static void applySettings(ResourceDescriptor settings);

    }; // ObjectFactory class
} // BattleRoom namespace
#endif // OBJECT_FACTORY_H


#ifndef BATTLE_ROOM_OBJECT_FACTORY_H
#define BATTLE_ROOM_OBJECT_FACTORY_H

#include "world/game_object.h"

namespace BattleRoom {

/**
 * Static class for creating Objects
 */
    class ObjectFactory {

    public:

        static std::vector<UniqueGameObject> getGameObjects(ResourceDescriptor settings);

        static UniqueGameObject createObjectOfDescription(ResourceDescriptor settings);

        static UniqueGameObject createObjectOfType(ObjectType type);

        static UniqueGameObject deserializeObject(BinaryStream& bs);

        static void applySettings(ResourceDescriptor settings);

        static ResourceDescriptor getSettings();

    }; // ObjectFactory class
} // BattleRoom namespace
#endif // BATTLE_ROOM_OBJECT_FACTORY_H


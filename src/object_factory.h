#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include "game_object.h"

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
#endif // OBJECT_FACTORY_H


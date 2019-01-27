#ifndef WORLD_H
#define WORLD_H

#include "resource.h"
#include "binary_stream.h"
#include "game_object.h"

#include <vector>

namespace BattleRoom {

    /**
     * Game world - includes all the objects, the time, and meta data
     */
    class World : public Resource {

    public:

        // constructors
        World();

        explicit World(ResourceDescriptor settings);

        World clone() const;

        const std::vector<UniqueGameObject> &getAllGameObjects() const; // TEMP
        const GameObject *getGameObject(UniqueId id) const;

        const std::vector<UniqueDrawableObject> &getBackgroundObjects() const;

        const GameObject *findIntersectingObject(Vector2D point) const;

        // getters
        seconds getGameTime() const;

        // inherited
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

        void serialize(BinaryStream &bs) const;

        static World deserialize(BinaryStream &bs);

    protected:

        std::vector<UniqueGameObject> m_gameObjects; // walls, stars, etc
        std::vector<UniqueDrawableObject> m_backgroundObjects; // background
        seconds m_gameTime; // Time in game

    }; // World class
} // BattleRoom namespace
#endif // WORLD_H

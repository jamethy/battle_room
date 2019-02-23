#ifndef BATTLE_ROOM_WORLD_H
#define BATTLE_ROOM_WORLD_H

#include "common/resource.h"
#include "common/binary_stream.h"
#include "world/game_object.h"

#include <vector>

namespace BattleRoom {

    class AlterWorld; // used in friend class def

    /**
     * Game world - includes all the objects, the time, and meta data.
     *
     * Just a container for the game world, does not do any updating
     */
    class World : public Resource {

    public:

        // constructors
        World();

        World clone() const;

        void copy(const World &other);

        /**
         * Get a reference to the game objects vector
         * I marked this as TEMP for some reason... maybe to limit views per player
         * @return Reference to game objects vector
         */
        const std::vector<UniqueGameObject> &getAllGameObjects() const;

        /**
         * Get a pointer to specific game object
         *
         * @param id Object to get
         * @return Pointer to object or nullptr
         */
        const GameObject *getGameObject(UniqueId id) const;

        /**
         * Get the reference to the list of background objects
         *
         * @return list of background objects
         */
        const std::vector<UniqueDrawableObject> &getBackgroundObjects() const;

        /**
         * Get which game object is under a 2d point on the z=0 plane
         *
         * @param point Intersecting point
         * @return Game object or nullptr
         */
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

        friend AlterWorld;

    }; // World class
} // BattleRoom namespace
#endif // BATTLE_ROOM_WORLD_H

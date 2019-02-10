#ifndef BATTLE_ROOM_LOCAL_UPDATING_WORLD_H
#define BATTLE_ROOM_LOCAL_UPDATING_WORLD_H

#include "world/world.h"
#include "world/game_time.h"

namespace BattleRoom {

    class AlterWorld;

    /**
     * Game world - includes all the objects, the time, and meta data
     */
    class LocalUpdatingWorld : public World {

    public:

        // constructors
        LocalUpdatingWorld();

        explicit LocalUpdatingWorld(ResourceDescriptor settings);

        /**
         * Update everything in the world. This will iterate the time
         * and updating everything else accordingly.
         */
        void update();

        // inherited
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    private:

        GameTime m_timeController; // Game time object
        UniqueBoundary m_boundary = nullptr; // limits of the world

        friend class AlterWorld;

    }; // LocalUpdatingWorld class
} // BattleRoom namespace
#endif // BATTLE_ROOM_LOCAL_UPDATING_WORLD_H

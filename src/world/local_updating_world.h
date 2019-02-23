#ifndef BATTLE_ROOM_LOCAL_UPDATING_WORLD_H
#define BATTLE_ROOM_LOCAL_UPDATING_WORLD_H

#include "world/world.h"
#include "world/game_time.h"

namespace BattleRoom {

    /**
     * Local updating world - contains the world and all the logic to update it
     */
    class LocalUpdatingWorld : public World {

    public:

        // constructors
        LocalUpdatingWorld();

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

    }; // LocalUpdatingWorld class
} // BattleRoom namespace
#endif // BATTLE_ROOM_LOCAL_UPDATING_WORLD_H

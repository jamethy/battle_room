#ifndef LOCAL_UPDATING_WORLD_H
#define LOCAL_UPDATING_WORLD_H

#include "world.h"
#include "game_time.h"

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
#endif // LOCAL_UPDATING_WORLD_H

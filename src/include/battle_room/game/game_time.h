#ifndef GAME_TIME_H
#define GAME_TIME_H

#include "battle_room/common/units.h"

#include <chrono>

namespace BattleRoom {

/**
 * Object containing time instance and alteration logic.
 */
    class GameTime {

    public:

        // constructor
        GameTime();

        /**
         * \brief Pauses the game time
         */
        void pause();

        /**
         * \breif Unpauses the game time
         */
        void unpause();

        /**
         * \brief Increments the game time (if not paused)
         */
        void update();

        // getters and setters
        seconds get();

        seconds getDelta();

        void set(seconds gameTime);

    private:

        seconds m_gameTime = 0.0; /// Game time to report
        seconds m_deltaTime = 0.0; /// Timestep made during last update
        bool m_paused = false; /// If game time should be incremented
        seconds m_timePaused = 0.0; /// Amount of physical time the game has been paused
        seconds m_startOffset = 0.0; /// Game resume time (for reloading games etc.)

        std::chrono::steady_clock::time_point m_startTime; /// Physical time the game was started

    }; // GameTime class
} // BattleRoom namespace
#endif // GAME_TIME_H

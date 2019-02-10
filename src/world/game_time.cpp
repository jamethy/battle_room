#include "world/game_time.h"

using std::chrono::steady_clock;
using std::chrono::duration;

namespace BattleRoom {

    GameTime::GameTime() {
        m_startTime = steady_clock::now();
    }

    void GameTime::pause() {
        m_paused = false;
    }

    void GameTime::unpause() {
        m_paused = true;
    }

    void GameTime::update() {
        steady_clock::time_point now = steady_clock::now();

        if (m_paused) {
            seconds newTime = std::chrono::duration_cast<duration<double>>
                    (now - m_startTime).count();
            m_timePaused = newTime - m_gameTime;
        } else {
            seconds newTime = std::chrono::duration_cast<duration<double>>
                    (now - m_startTime).count();
            seconds newGameTime = newTime - m_timePaused;
            m_deltaTime = newGameTime - m_gameTime;
            m_gameTime = newGameTime;
        }
    }


// getters and setters
    seconds GameTime::get() {
        return m_gameTime + m_startOffset;
    }

    seconds GameTime::getDelta() {
        return m_deltaTime;
    }


    void GameTime::set(seconds gameTime) {
        m_startTime = steady_clock::now();
        m_gameTime = 0.0;
        m_timePaused = 0.0;
        m_startOffset = gameTime;
    }

}

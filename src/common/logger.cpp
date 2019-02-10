//
// Created by james on 1/12/19.
//

#include <iostream>
#include <chrono>
#include "common/logger.h"

using std::chrono::steady_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;


namespace BattleRoom {


    long getTimeStamp() {
        auto timeSinceEpoch = steady_clock::now().time_since_epoch();
        return duration_cast<milliseconds>(timeSinceEpoch).count();
    }

    Log::Level Log::Log::m_level = DEBUG;

    void Log::setLevel(Log::Level level) {
        m_level = level;
    }

    Log::Level Log::getLevel() {
        return m_level;
    }
}

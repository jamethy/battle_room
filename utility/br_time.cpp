#include "br_time.h"
#include "chrono"

namespace Utility {

typedef std::chrono::steady_clock clock;
typedef std::chrono::duration<double> seconds;

class ChronoTime
{
public:
    ChronoTime();
    ~ChronoTime();
    double getTime();
    void pauseTime();
    void unpauseTime();
    void resetTime(double offset);
private:

    clock::time_point m_start;
    double m_offset = 0;
    double m_pausedTime = 0;
    clock::time_point m_timeAtPause;
    bool m_paused = false;
};

ChronoTime::ChronoTime() :
    m_start(clock::now()),
    m_offset(0)
{
}

ChronoTime::~ChronoTime(){}

double ChronoTime::getTime()
{
    seconds time_span = std::chrono::duration_cast< seconds > (clock::now() - m_start);
    return time_span.count() + m_offset - m_pausedTime;
}


void ChronoTime::pauseTime()
{
    if(!m_paused)
    {
        m_timeAtPause = clock::now();
        m_paused = true;
    }
}

void ChronoTime::unpauseTime()
{
    if(m_paused)
    {
        seconds time_span = std::chrono::duration_cast< seconds > (clock::now() - m_timeAtPause);
        m_pausedTime += time_span.count();
        m_paused = false;
    }
}

void ChronoTime::resetTime(double offset)
{
    m_start = clock::now();
    m_offset = offset;
    m_pausedTime = 0;
}

ChronoTime m_time;

double getTime(){ return m_time.getTime(); }
void pauseTime(){ m_time.pauseTime(); }
void unpauseTime(){ m_time.unpauseTime(); }
void resetTime(double offset){ m_time.resetTime(offset); }

} // Utility namespace

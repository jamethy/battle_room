#include "br_time.h"
#include "chrono"

namespace Utility {

TimeBase* TimeBase::m_time = nullptr;
TimeBase::~TimeBase(){}


typedef std::chrono::steady_clock clock;
typedef std::chrono::duration<double> seconds;

class ChronoTime : public TimeBase
{
public:
    ChronoTime();
    ~ChronoTime();
    double m_getTime();
    void m_resetTime(double offset);
private:

    clock::time_point m_start;
    double m_offset = 0;
};

ChronoTime::ChronoTime() :
    m_start(clock::now()),
    m_offset(0)
{
}

ChronoTime::~ChronoTime(){}

double ChronoTime::m_getTime()
{
    seconds time_span = std::chrono::duration_cast< seconds > (clock::now() - m_start);
    return time_span.count() + m_offset;
}

void ChronoTime::m_resetTime(double offset)
{
    m_start = clock::now();
    m_offset = offset;
}



double TimeBase::getTime()
{
    if(m_time == nullptr) m_time = new ChronoTime();
    return m_time->getTime();
}

void TimeBase::resetTime(double offset)
{
    if(m_time == nullptr) m_time = new ChronoTime();
    m_time->resetTime(offset);
}

} // Utility namespace

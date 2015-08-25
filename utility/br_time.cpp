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
    void resetTime(double offset);
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

double ChronoTime::getTime()
{
    seconds time_span = std::chrono::duration_cast< seconds > (clock::now() - m_start);
    return time_span.count() + m_offset;
}

void ChronoTime::resetTime(double offset)
{
    m_start = clock::now();
    m_offset = offset;
}

ChronoTime m_time;

double getTime()
{
    return m_time.getTime();
}

void resetTime(double offset)
{
    m_time.resetTime(offset);
}

} // Utility namespace

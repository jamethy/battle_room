#ifndef BR_TIME_H
#define BR_TIME_H

#include <memory>

namespace Utility {

class TimeBase
{
private:
    static TimeBase* m_time;
protected:
    TimeBase(){}
    virtual double m_getTime() = 0;
    virtual void m_resetTime(double offset) = 0;
public:
    virtual ~TimeBase();
    static double getTime();
    static void resetTime(double offset);


};

} // Utility namespace

#endif // BR_TIME_H

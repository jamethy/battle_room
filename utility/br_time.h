#ifndef BR_TIME_H
#define BR_TIME_H

#include <memory>

namespace Utility {

double getTime();
void pauseTime();
void unpauseTime();
void resetTime(double offset);

} // Utility namespace

#endif // BR_TIME_H

#ifndef FRAME_H
#define FRAME_H

#include "battle_room/common/pixel.h"
#include "battle_room/common/resource_descriptor.h"

namespace Animation {

typedef double seconds;

class Frame {

public:

    Frame(seconds endTime, Common::Pixel topLeft, Common::Pixel bottomRight, 
            double xScale, double yScale);

    seconds getEndTime();

    const Common::Pixel& getTopLeft();
    const Common::Pixel& getBottomRight();

    double getXScale();
    double getYScale();


private:
    
    const seconds m_endTime;

    const Common::Pixel m_topLeft;
    const Common::Pixel m_bottomRight;

    const double m_xScale; // meters per pixel
    const double m_yScale; // meters per pixel
    
}; // Frame class


/**
 * Parses the string for seconds
 */
seconds toSeconds(std::string str);


} // Animation namespace
#endif // FRAME_H

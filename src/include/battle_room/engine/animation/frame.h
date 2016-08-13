#ifndef FRAME_H
#define FRAME_H

#include "battle_room/common/pixel.h"
#include "battle_room/common/resource_descriptor.h"

namespace BattleRoom {

typedef double seconds;

class Frame {

public:


    Frame(ResourceDescriptor descriptor);

    seconds getEndTime();

    const Pixel& getTopLeft();
    const Pixel& getBottomRight();

    double getXScale();
    double getYScale();


private:
    
    seconds m_endTime;

    Pixel m_topLeft;
    Pixel m_bottomRight;

    double m_xScale; // meters per pixel
    double m_yScale; // meters per pixel
    
}; // Frame class


/**
 * Parses the string for seconds
 */
seconds toSeconds(std::string str);


} // BattleRoom namespace
#endif // FRAME_H

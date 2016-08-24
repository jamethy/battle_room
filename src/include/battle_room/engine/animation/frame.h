#ifndef FRAME_H
#define FRAME_H

#include "battle_room/common/pixel.h"
#include "battle_room/common/resource_descriptor.h"

namespace BattleRoom {

/**
 * Unit of measurement for time
 */
typedef double seconds;

/**
 * \brief Frame in an animation. Each frame cuts out a portion of
 * the image file and has an end time to mark its point in the 
 * animation.
 *
 * These objects is also constant and should never change
 */
class Frame {

public:

    // Constructors
    Frame(ResourceDescriptor descriptor);

    // getters
    seconds getEndTime() const;

    const Pixel& getTopLeft() const;
    const Pixel& getBottomRight() const;

    double getXScale() const;
    double getYScale() const;


private:
    
    seconds m_endTime; ///< Time to move to next frame

    Pixel m_topLeft; ///< Position of the top-left of the frame in the image
    Pixel m_bottomRight; ///< Position of the bottom-rightof the frame in the image

    double m_xScale; // meters per pixel, amount to stretch image
    double m_yScale; // meters per pixel, amount to stretch image
    
}; // Frame class


/**
 * \brief Parses the string for seconds
 * \param str String containing seconds to parse
 * \return Seconds value found in str
 */
seconds toSeconds(std::string str);


} // BattleRoom namespace
#endif // FRAME_H

#include "battle_room/engine/animation/frame.h"

using Common::Pixel;

namespace Animation {

Frame::Frame(seconds endTime, Pixel topLeft, Pixel bottomRight, double xScale, double yScale)
    : m_endTime(endTime), 
    m_topLeft(topLeft), m_bottomRight(bottomRight), 
    m_xScale(xScale), m_yScale(yScale)
{ }

seconds Frame::getEndTime() {
    return m_endTime;
}

const Pixel& Frame::getTopLeft() {
    return m_topLeft;
}

const Pixel& Frame::getBottomRight() {
    return m_bottomRight;
}

double Frame::getXScale() {
    return m_xScale;
}

double Frame::getYScale() {
    return m_yScale;
}

} // Animation namespace

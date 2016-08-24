#include "battle_room/engine/animation/frame.h"

namespace BattleRoom {

// constructor

Frame::Frame(ResourceDescriptor descriptor) {
    
    ResourceDescriptor sub = descriptor.getSubResource("EndTime");
    if (!sub.getKey().empty()) {
        m_endTime = toSeconds(sub.getValue());
    }

    sub = descriptor.getSubResource("TopRow");
    if (!sub.getKey().empty()) {
        m_topLeft.setRow( toPx(sub.getValue()) );
    }

    sub = descriptor.getSubResource("LeftCol");
    if (!sub.getKey().empty()) {
        m_topLeft.setCol( toPx(sub.getValue()) );
    }

    sub = descriptor.getSubResource("BottomRow");
    if (!sub.getKey().empty()) {
        m_bottomRight.setRow( toPx(sub.getValue()) );
    }

    sub = descriptor.getSubResource("RightCol");
    if (!sub.getKey().empty()) {
        m_bottomRight.setCol( toPx(sub.getValue()) );
    }

    sub = descriptor.getSubResource("XScale");
    if (!sub.getKey().empty()) {
        m_xScale = toPx(sub.getValue());
    }

    sub = descriptor.getSubResource("YScale");
    if (!sub.getKey().empty()) {
        m_yScale = toPx(sub.getValue());
    }
}

// getters

seconds Frame::getEndTime() const {
    return m_endTime;
}

const Pixel& Frame::getTopLeft() const {
    return m_topLeft;
}

const Pixel& Frame::getBottomRight() const {
    return m_bottomRight;
}

double Frame::getXScale() const {
    return m_xScale;
}

double Frame::getYScale() const {
    return m_yScale;
}


// other functions

seconds toSeconds(std::string str) {
    return stod(str);
}

} // BattleRoom namespace

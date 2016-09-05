#include "battle_room/engine/animation/frame.h"

namespace BattleRoom {

// apply settings

void Frame::applySettings(ResourceDescriptor settings) {

    ResourceDescriptor sub = settings.getSubResource("EndTime");
    if (!sub.getKey().empty()) {
        m_endTime = toSeconds(sub.getValue());
    }

    sub = settings.getSubResource("TopLeft");
    if (!sub.getKey().empty()) {
        m_topLeft.applySettings(sub);
    }

    sub = settings.getSubResource("BottomRight");
    if (!sub.getKey().empty()) {
        m_bottomRight.applySettings(sub);
    }

    sub = settings.getSubResource("XScale");
    if (!sub.getKey().empty()) {
        m_xScale = toPx(sub.getValue());
    }

    sub = settings.getSubResource("YScale");
    if (!sub.getKey().empty()) {
        m_yScale = toPx(sub.getValue());
    }
}

// constructor

Frame::Frame(ResourceDescriptor descriptor) {
    applySettings(descriptor);   
}

// getters

seconds Frame::getEndTime() const {
    return m_endTime;
}

double Frame::getXScale() const {
    return m_xScale;
}

double Frame::getYScale() const {
    return m_yScale;
}

const Pixel& Frame::getTopLeft() const {
    return m_topLeft;
}

const Pixel& Frame::getBottomRight() const {
    return m_bottomRight;
}

meters Frame::getWidth() const {
    return m_xScale*(m_bottomRight.getCol() - m_topLeft.getCol());
}

meters Frame::getHeight() const {
    return m_yScale*(m_bottomRight.getRow() - m_topLeft.getRow());
}


// other functions

seconds toSeconds(std::string str) {
    return stod(str);
}

} // BattleRoom namespace

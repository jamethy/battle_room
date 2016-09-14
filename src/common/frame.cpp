#include "battle_room/common/frame.h"

namespace BattleRoom {

// apply settings

void Frame::applySettings(ResourceDescriptor settings) {

    m_topLeft.applySettings( settings.getSubResource("TopLeft") );
    m_bottomRight.applySettings( settings.getSubResource("BottomRight") );

    ResourceDescriptor sub = settings.getSubResource("EndTime");
    if (isNotEmpty(sub.getValue())) {
        m_endTime = toSeconds(sub.getValue());
    }

    sub = settings.getSubResource("XScale");
    if (isNotEmpty(sub.getValue())) {
        m_xScale = toPx(sub.getValue());
    }

    sub = settings.getSubResource("YScale");
    if (isNotEmpty(sub.getValue())) {
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

} // BattleRoom namespace

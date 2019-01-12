#include "frame.h"

namespace BattleRoom {

// apply settings

    void Frame::applySettings(ResourceDescriptor settings) {

        m_topLeft.applySettings(settings.getSubResource("TopLeft"));
        m_bottomRight.applySettings(settings.getSubResource("BottomRight"));

        ResourceDescriptor sub = settings.getSubResource("EndTime");
        if (isNotEmpty(sub.getValue())) {
            m_endTime = toSeconds(sub.getValue());
        }

        sub = settings.getSubResource("Scale");
        if (isNotEmpty(sub.getValue())) {
            m_scale = toPx(sub.getValue());
        }

        sub = settings.getSubResource("Flip");
        if (isNotEmpty(sub.getValue())) {
            m_flip = sub.getValue();
        }

        m_boundarySet = BoundarySet(settings.getSubResources("Boundary"));
    }

// constructor

    Frame::Frame(ResourceDescriptor descriptor) :
        m_scale(1), m_flip("none")
    {
        applySettings(descriptor);
    }

// getters

    seconds Frame::getEndTime() const {
        return m_endTime;
    }

    double Frame::getScale() const {
        return m_scale;
    }

    const Pixel &Frame::getTopLeft() const {
        return m_topLeft;
    }

    const Pixel &Frame::getBottomRight() const {
        return m_bottomRight;
    }

    meters Frame::getWidth() const {
        return m_scale * (m_bottomRight.getCol() - m_topLeft.getCol());
    }

    meters Frame::getHeight() const {
        return m_scale * (m_bottomRight.getRow() - m_topLeft.getRow());
    }

    std::string Frame::getFlip() const {
        return m_flip;
    }

    const BoundarySet &Frame::getBoundarySet() const {
        return m_boundarySet;
    }

} // BattleRoom namespace
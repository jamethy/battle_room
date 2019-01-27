#include <utility>

#include "frame.h"

using std::to_string;

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

    ResourceDescriptor Frame::getSettings() const {
        ResourceDescriptor rd("Frame", "");
        std::vector<ResourceDescriptor> subs;
        subs.clear();

        ResourceDescriptor sub = m_topLeft.getSettings();
        sub.setKey("TopLeft");
        subs.push_back(sub);

        sub = m_bottomRight.getSettings();
        sub.setKey("BottomRight");
        subs.push_back(sub);

        subs.emplace_back("EndTime", to_string(m_endTime));
        subs.emplace_back("Scale", to_string(m_scale));
        subs.emplace_back("Flip", m_flip);

        for (const auto &boundary : m_boundarySet) {
            subs.push_back(boundary->getSettings());
        }

        rd.setSubResources(subs);
        return rd;
    }

// constructor

    Frame::Frame(ResourceDescriptor descriptor) :
            m_scale(1), m_flip("none") {
        applySettings(std::move(descriptor));
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

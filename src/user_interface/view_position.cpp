#include "battle_room/user_interface/view_position.h"

namespace BattleRoom {

    // defined later
    ScreenAnchor parseScreenAnchor(std::string str);
    SizeType parseSizeType(const std::string str);

    // apply settings
    void ViewPosition::applySettings(ResourceDescriptor settings) {

        m_sizeType = parseSizeType(settings.getValue());
        m_anchor = parseScreenAnchor(settings.getSubResource("ScreenAnchor").getValue());

        if (SizeType::Absolute == m_sizeType) {
            m_topLeft.applySettings(settings.getSubResource("TopLeft"));
            m_bottomRight.applySettings(settings.getSubResource("BottomRight"));

        } else if (SizeType::Anchored == m_sizeType) {
            Pixel topLeft, botRight;
            topLeft.applySettings(settings.getSubResource("TopLeft"));
            botRight.applySettings(settings.getSubResource("BottomRight"));

            setAnchoredPosition(topLeft, botRight);

        } else if (SizeType::Relative == m_sizeType) {
            Pixel anchor;
            double ratio = stod(settings.getSubResource("Ratio").getValue());
            double scale = stod(settings.getSubResource("Scale").getValue());
            anchor.applySettings(settings.getSubResource("Anchor"));

            setRelativePosition(anchor, scale, scale/ratio);

        } else if (SizeType::Fill == m_sizeType) {
            m_topLeft = Pixel(0, 0);
            m_bottomRight = Pixel(m_windowHeight, m_windowWidth);
        }
    }

    // constructor
    ViewPosition::ViewPosition(ResourceDescriptor settings, int windowWidth, int windowHeight) :
        m_anchor(ScreenAnchor::TopLeft),
        m_windowWidth(windowWidth),
        m_windowHeight(windowHeight)
    {
        applySettings(settings);
    }

    Pixel ViewPosition::getTopLeft() const {
        return m_topLeft;
    }

    Pixel ViewPosition::getBottomRight() const {
        return m_bottomRight;
    }

    void ViewPosition::adjustAnchoredPosition(px oldWidth, px oldHeight) {

        Pixel topLeft;

        switch (m_anchor) {
            case TopRight: 
                topLeft = Pixel(m_topLeft.getRow(), oldWidth - m_topLeft.getCol());
                break;
            case BottomLeft: 
                topLeft = Pixel(oldHeight - m_topLeft.getRow(), m_topLeft.getCol());
                break;
            case BottomRight: 
                topLeft = Pixel(oldHeight - m_topLeft.getRow(), oldWidth - m_topLeft.getCol());
                break;
            case Center:
                topLeft = Pixel(m_topLeft.getRow() - oldHeight/2, m_topLeft.getCol() - oldWidth/2);
                break;
            case TopLeft: 
            default:
                topLeft = m_topLeft;
                break;
        }

        Pixel botRight = Pixel(topLeft.getRow() + (m_bottomRight.getRow() - m_topLeft.getRow()), topLeft.getCol() + (m_bottomRight.getCol() - m_topLeft.getCol()));
        setAnchoredPosition(topLeft, botRight);
    }

    void ViewPosition::adjustRelativePosition(px oldWidth, px oldHeight) {
        Pixel anchor; 
        px viewWidth = m_bottomRight.getCol() - m_topLeft.getCol(); 
        px viewHeight = m_bottomRight.getRow() - m_topLeft.getRow();

        switch (m_anchor) {
            case TopRight: 
                anchor = Pixel(m_topLeft.getRow(), oldWidth - m_bottomRight.getCol());
                break;
            case BottomLeft: 
                anchor = Pixel(oldHeight - m_bottomRight.getRow(), m_topLeft.getCol());
                break;
            case BottomRight: 
                anchor = Pixel(oldHeight - m_bottomRight.getRow(), oldWidth - m_bottomRight.getCol());
                break;
            case Center:
                anchor = Pixel(m_topLeft.getRow() - (oldHeight - viewHeight)/2, m_topLeft.getCol() - (oldWidth - viewWidth)/2);
                break;
            case TopLeft: 
            default:
                anchor = m_topLeft;
                break;
        }


        setRelativePosition(anchor, viewWidth, viewHeight);
    }

    void ViewPosition::adjustForResize(int width, int height, int oldWidth, int oldHeight) {

        m_windowWidth = width;
        m_windowHeight = height;

        switch (m_sizeType) {
            case SizeType::Absolute:
                break;

            case SizeType::Anchored:
                adjustAnchoredPosition(oldWidth, oldHeight);
                break;

            case SizeType::Relative:
                adjustRelativePosition(oldWidth, oldHeight);
                break;

            case SizeType::Fill:
            default:
                m_bottomRight = Pixel(height, width);
                break;
        }
    }

    void ViewPosition::setAnchoredPosition(Pixel topLeft, Pixel botRight) {
        switch (m_anchor) {
            case TopRight: 
                m_topLeft = Pixel(topLeft.getRow(), m_windowWidth - topLeft.getCol());
                break;
            case BottomLeft: 
                m_topLeft = Pixel(m_windowHeight - topLeft.getRow(), topLeft.getCol());
                break;
            case BottomRight: 
                m_topLeft = Pixel(m_windowHeight - topLeft.getRow(), m_windowWidth - topLeft.getCol());
                break;
            case Center:
                m_topLeft = Pixel(m_windowHeight/2.0 + topLeft.getRow(), m_windowWidth/2.0 + topLeft.getCol());
                break;
            case TopLeft: 
            default:
                m_topLeft = topLeft;
                break;
        }

        px width = botRight.getCol() - topLeft.getCol();
        px height = botRight.getRow() - topLeft.getRow();
        m_bottomRight = Pixel(m_topLeft.getRow() + height, m_topLeft.getCol() + width);

    }

    void ViewPosition::setRelativePosition(Pixel anchor, px width, px height) {
        switch (m_anchor) {
            case TopRight: 
                m_topLeft = Pixel(anchor.getRow(), m_windowWidth - (anchor.getCol() + width));
                break;
            case BottomLeft: 
                m_topLeft = Pixel(m_windowHeight - (anchor.getRow() + height), anchor.getCol());
                break;
            case BottomRight: 
                m_topLeft = Pixel(m_windowHeight - (anchor.getRow() + height), m_windowWidth - (anchor.getCol() + width));
                break;
            case Center:
                m_topLeft = Pixel(m_windowHeight/2.0 - height/2.0 + anchor.getRow(), m_windowWidth/2.0 - width/2.0 + anchor.getCol());
                break;
            case TopLeft: 
            default:
                m_topLeft = anchor;
                break;
        }

        m_bottomRight = Pixel(m_topLeft.getRow() + height, m_topLeft.getCol() + width);
    }

    SizeType parseSizeType(const std::string str) {
        if (keyMatch(str, "Absolute")) {
            return SizeType::Absolute;
        } else if (keyMatch(str, "Anchored")) {
            return SizeType::Anchored;
        } else if (keyMatch(str, "Relative")) {
            return SizeType::Relative;
        } else {
            return SizeType::Fill;
        }
    }

    ScreenAnchor parseScreenAnchor(std::string str) {
        if (keyMatch("TopRight", str)) {
            return ScreenAnchor::TopRight;
        } else if (keyMatch("BottomLeft", str)) {
            return ScreenAnchor::BottomLeft;
        } else if (keyMatch("BottomRight", str)) {
            return ScreenAnchor::BottomRight;
        } else if (keyMatch("Center", str)) {
            return ScreenAnchor::Center;
        } else {
            return ScreenAnchor::TopLeft;
        }
    }

} // BattleRoom namespace


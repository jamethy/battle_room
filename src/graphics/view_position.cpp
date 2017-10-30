#include "battle_room/graphics/view_position.h"
#include <iostream>

namespace BattleRoom {

    SizeType parseSizeType(const std::string str) {
        std::cout << "str: " << str << std::endl;
        if (keyMatch(str, "Absolute")) {
            std::cout << " absolute\n";
            return SizeType::Absolute;
        } else if (keyMatch(str, "Anchored")) {
            return SizeType::Anchored;
        } else if (keyMatch(str, "Relative")) {
            return SizeType::Relative;
        } else {
            return SizeType::Fill;
        }
    }

    void ViewPosition::applySettings(ResourceDescriptor settings) {

        m_sizeType = parseSizeType(settings.getValue());
        m_topLeft.applySettings(settings.getSubResource("TopLeft"));
        m_bottomRight.applySettings(settings.getSubResource("BottomRight"));

        if (SizeType::Fill == m_sizeType) {
            m_bottomRight = Pixel(m_windowHeight, m_windowWidth);
        }
    }

    ViewPosition::ViewPosition(ResourceDescriptor settings, int windowWidth, int windowHeight) :
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

    void ViewPosition::adjustForResize(int width, int height, int oldWidth, int oldHeight) {

        m_windowWidth = width;
        m_windowHeight = height;

        switch (m_sizeType) {
            case SizeType::Absolute:
                break;
            case SizeType::Fill:
                m_bottomRight = Pixel(height, width);
                break;
            case SizeType::Anchored:
            case SizeType::Relative:
            default:
                m_topLeft = Pixel(
                        height * getTopLeft().getRow() / oldHeight,
                        width * getTopLeft().getCol() / oldWidth
                        );

                m_bottomRight = Pixel(
                        height * getBottomRight().getRow() / oldHeight,
                        width * getBottomRight().getCol() / oldWidth
                        );
        }
    }

} // BattleRoom namespace


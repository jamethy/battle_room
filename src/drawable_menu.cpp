#include "drawable_menu.h"
#include "animation_handler.h"
#include "Logger.h"

namespace BattleRoom {

// apply settings

    void DrawableMenu::applySettings(ResourceDescriptor settings) {

        m_topLeft.applySettings(settings.getSubResource("TopLeft"));
        m_bottomRight.applySettings(settings.getSubResource("BottomRight"));

        ResourceDescriptor sub = settings.getSubResource("ZLayer");
        if (isNotEmpty(sub.getValue())) {
            setZLayer(stod(sub.getValue()));
        }
    }

// Constructor

    DrawableMenu::DrawableMenu() :
            m_zLayer(0.0),
            m_topLeft(RelPixel(0, 0)),
            m_bottomRight(RelPixel(1, 1)) {
    }

    DrawableMenu::~DrawableMenu() = default;

// other functions

// getters and setters

    std::string DrawableMenu::getTextureKey() const {
        return m_textureKey;
    }

    void DrawableMenu::setTextureKey(const std::string &textureKey) {
        m_textureKey = textureKey;
    }

    RelPixel DrawableMenu::getTopLeft() const {
        return m_topLeft;
    }

    RelPixel DrawableMenu::getBottomRight() const {
        return m_bottomRight;
    }

    double DrawableMenu::getZLayer() const {
        return m_zLayer;
    }

    void DrawableMenu::setTopLeft(RelPixel topLeft) {
        m_topLeft = topLeft;
    }

    void DrawableMenu::setBottomRight(RelPixel bottomRight) {
        m_bottomRight = bottomRight;
    }

    void DrawableMenu::setZLayer(double zLayer) {
        m_zLayer = zLayer;
    }

} // BattleRoom namespace


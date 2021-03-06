#include "display_window/drawable_menu.h"
#include "animation/animation_handler.h"
#include "common/logger.h"

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

    ResourceDescriptor DrawableMenu::getSettings() const {
        ResourceDescriptor rd;
        std::vector<ResourceDescriptor> subs = {};

        ResourceDescriptor sub = m_topLeft.getSettings();
        sub.setKey("TopLeft");
        subs.push_back(sub);

        sub = m_bottomRight.getSettings();
        sub.setKey("BottomRight");
        subs.push_back(sub);

        subs.emplace_back("ZLayer", std::to_string(getZLayer()));

        rd.setSubResources(subs);
        return rd;
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


#ifndef BATTLE_ROOM_DRAWABLE_MENU_H
#define BATTLE_ROOM_DRAWABLE_MENU_H

#include <third_party/cef/cef_binary_3.3396.1777.g636f29b_linux64/include/internal/cef_ptr.h>
#include "common/resource.h"
#include "common/vector2d.h"
#include "animation/animation.h"
#include "common/rel_pixel.h"
#include "views/web_browser_client.h"
#include "views/web_renderer.h"
#include "application/input.h"

namespace BattleRoom {

    /**
     * \brief Object that is drawable on a view
     */
    class DrawableMenu : public Resource {

    public:

        // constructor
        DrawableMenu();

        ~DrawableMenu() override;

        // getters and setters
        std::string getTextureKey() const;

        void setTextureKey(const std::string &textureKey);

        RelPixel getTopLeft() const;

        RelPixel getBottomRight() const;

        double getZLayer() const;

        void setTopLeft(RelPixel topLeft);

        void setBottomRight(RelPixel bottomRight);

        void setZLayer(double zLayer);

        // inherited
        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    private:

        double m_zLayer;
        RelPixel m_topLeft;
        RelPixel m_bottomRight;

        std::string m_textureKey;
    }; // DrawableMenu class
} // BattleRoom namespace
#endif // BATTLE_ROOM_DRAWABLE_MENU_H

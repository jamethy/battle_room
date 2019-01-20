#ifndef DRAWABLE_MENU_H
#define DRAWABLE_MENU_H

#include <third_party/cef/cef_binary_3.3396.1777.g636f29b_linux64/include/internal/cef_ptr.h>
#include "resource.h"
#include "vector2d.h"
#include "animation.h"
#include "rel_pixel.h"
#include "web_browser_client.h"
#include "web_renderer.h"
#include "input.h"

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
        void setTextureKey(const std::string& textureKey);

        RelPixel getTopLeft() const;

        RelPixel getBottomRight() const;

        double getZLayer() const;

        void setTopLeft(RelPixel topLeft);

        void setBottomRight(RelPixel bottomRight);

        void setZLayer(double zLayer);

        // inherited
        virtual void applySettings(ResourceDescriptor settings) override;

    private:

        double m_zLayer;
        RelPixel m_topLeft;
        RelPixel m_bottomRight;

        std::string m_textureKey;
    }; // DrawableMenu class
} // BattleRoom namespace
#endif // DRAWABLE_MENU_H

#ifndef DRAWABLE_MENU_H
#define DRAWABLE_MENU_H

#include "resource.h"
#include "vector2d.h"
#include "animation.h"
#include "rel_pixel.h"

namespace BattleRoom {

/**
 * \brief Object that is drawable on a view
 */
    class DrawableMenu : public Resource {

    public:

        // constructor
        DrawableMenu();
        ~DrawableMenu();

        // getters and setters
        std::string getTextureKey() const;

        RelPixel getTopLeft() const;

        RelPixel getBottomRight() const;

        double getZLayer() const;

        void setTextureKey(const std::string& textureKey);

        void setTopLeft(RelPixel topLeft);

        void setBottomRight(RelPixel bottomRight);

        void setZLayer(double zLayer);

        // inherited
        virtual void applySettings(ResourceDescriptor settings) override;

    private:

        std::string m_textureKey;
        double m_zLayer;
        RelPixel m_topLeft;
        RelPixel m_bottomRight;

    }; // DrawableMenu class
} // BattleRoom namespace
#endif // DRAWABLE_MENU_H

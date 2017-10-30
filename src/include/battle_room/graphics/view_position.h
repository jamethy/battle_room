#ifndef VIEW_POSITION_H
#define VIEW_POSITION_H

#include "battle_room/common/resource.h"
#include "battle_room/common/pixel.h"
#include "battle_room/graphics/screen_anchor.h"

namespace BattleRoom {

    enum SizeType {
        Absolute, Fill, Anchored, Relative
    };

    class ViewPosition : public Resource {
        public:

            ViewPosition(ResourceDescriptor settings, int windowWidth, int windowHeight);

            Pixel getTopLeft() const;

            Pixel getBottomRight() const;

            void adjustForResize(int width, int height, int oldWidth, int oldHeight);

            void applySettings(ResourceDescriptor settings) override;

        private:

            Pixel m_topLeft; ///< Coordinate of top left of the view on the display window
            Pixel m_bottomRight; ///< Coordinate of bottom rightof the view on the display window

            SizeType m_sizeType;

            ScreenAnchor m_anchor;
            px m_width;
            px m_height;
            double m_ratio;
            double m_scale;

            px m_windowWidth;
            px m_windowHeight;
            
            //positioning
                // abs = topleft, botright
                // fill = none
                // rel = anchor, width, height
                // rel = ancho, ratio, scale

    };
} // BattleRoom namespace
#endif // VIEW_POSITION_H

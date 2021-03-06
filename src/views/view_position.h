#ifndef BATTLE_ROOM_VIEW_POSITION_H
#define BATTLE_ROOM_VIEW_POSITION_H

#include "common/resource.h"
#include "common/pixel.h"
#include "views/screen_anchor.h"

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

        int getViewWidth() const;

        int getViewHeight() const;

        void applySettings(ResourceDescriptor settings) override;

        ResourceDescriptor getSettings() const override;

    private:

        void setAnchoredPosition(Pixel topLeft, Pixel botRight);

        void setRelativePosition(Pixel anchor, px width, px height);

        void adjustAnchoredPosition(px oldWidth, px oldHeight);

        void adjustRelativePosition(px oldWindowWidth, px oldWindowHeight);

        Pixel m_topLeft; ///< Coordinate of top left of the view on the display window
        Pixel m_bottomRight; ///< Coordinate of bottom rightof the view on the display window

        SizeType m_sizeType;
        ScreenAnchor m_anchor;


        px m_windowWidth;
        px m_windowHeight;

        //positioning
        // abs = topleft, botright
        // fill = none
        // anchored = anchor, width, height
        // rel = ancho, ratio, scale

    };
} // BattleRoom namespace
#endif // BATTLE_ROOM_VIEW_POSITION_H

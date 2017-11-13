#ifndef DRAWABLE_MENU_H
#define DRAWABLE_MENU_H

#include "battle_room/common/resource.h"
#include "battle_room/common/vector2d.h"
#include "battle_room/common/animation.h"
#include "battle_room/common/rel_pixel.h"

namespace BattleRoom {

/**
 * \brief Object that is drawable on a view
 */
    class DrawableMenu : public Resource {

    public:

        // constructor
        DrawableMenu();
        ~DrawableMenu() {}

        // getters and setters

        Animation &getAnimation() const;

        seconds getAnimationState() const;

        RelPixel getTopLeft() const;

        RelPixel getBottomRight() const;

        std::string getText() const;

        double getZLayer() const;

        void updateAnimation(seconds timestep);

        void setAnimation(Animation &animation);

        void setAnimationState(seconds animationState);

        void setTopLeft(RelPixel topLeft);

        void setBottomRight(RelPixel bottomRight);

        void setText(std::string text);

        void setZLayer(double zLayer);

        // inherited
        virtual void applySettings(ResourceDescriptor settings) override;

    private:

        Animation *m_currentAnimation; ///< Animation object is on
        seconds m_animationState; ///< Seconds into animation
        double m_zLayer;
        RelPixel m_topLeft;
        RelPixel m_bottomRight;
        std::string m_text;

    }; // DrawableMenu class
} // BattleRoom namespace
#endif // DRAWABLE_MENU_H

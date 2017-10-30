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

        // getters and setters

        Animation &getAnimation() const;

        seconds getAnimationState() const;

        RelPixel getTopLeft() const;

        RelPixel getBottomRight() const;

        void updateAnimation(seconds timestep);

        void setAnimation(Animation &animation);

        void setAnimationState(seconds animationState);

        void setTopLeft(RelPixel topLeft);

        void setBottomRight(RelPixel bottomRight);

        // inherited
        virtual void applySettings(ResourceDescriptor settings) override;

    private:

        Animation *m_currentAnimation; ///< Animation object is on
        seconds m_animationState; ///< Seconds into animation
        RelPixel m_topLeft;
        RelPixel m_bottomRight;

    }; // DrawableMenu class
} // BattleRoom namespace
#endif // DRAWABLE_MENU_H

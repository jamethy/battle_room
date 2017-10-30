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

        Vector2D getLocation() const;

        relpx getWidth() const;

        relpx getHeight() const;

        void updateAnimation(seconds timestep);

        void setAnimation(Animation &animation);

        void setAnimationState(seconds animationState);

        void setLocation(Vector2D location);

        void setWidth(relpx width);

        void setHeight(relpx height);

        // inherited
        virtual void applySettings(ResourceDescriptor settings) override;

    private:

        Animation *m_currentAnimation; ///< Animation object is on
        seconds m_animationState; ///< Seconds into animation
        Vector2D m_location; ///< Location of the object in 2D space 0-1
        relpx m_width;
        relpx m_height;

    }; // DrawableMenu class
} // BattleRoom namespace
#endif // DRAWABLE_MENU_H

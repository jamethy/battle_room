#include "battle_room/common/drawable_menu.h"
#include "battle_room/common/animation_handler.h"

namespace BattleRoom {

// apply settings

    void DrawableMenu::applySettings(ResourceDescriptor settings) {

        m_topLeft.applySettings(settings.getSubResource("TopLeft"));
        m_bottomRight.applySettings(settings.getSubResource("BottomRight"));

        ResourceDescriptor sub = settings.getSubResource("Animation");
        if (isNotEmpty(sub.getValue())) {
            setAnimation(AnimationHandler::getAnimation(sub.getValue()));
        }

        sub = settings.getSubResource("AnimationState");
        if (isNotEmpty(sub.getValue())) {
            setAnimationState(toSeconds(sub.getValue()));
        }
    }

// Constructor

    DrawableMenu::DrawableMenu() :
            m_currentAnimation(&AnimationHandler::getAnimation(MISSING_ANIMATION)),
            m_animationState(0.0),
            m_topLeft(RelPixel(0,0)),
            m_bottomRight(RelPixel(1,1))
    {}

// other functions

    void DrawableMenu::updateAnimation(seconds timestep) {
        Animation &animation = getAnimation();
        seconds newState = getAnimationState() + timestep;

        if (newState > animation.getLength()) {

            // set the new state (time elapsed since end of last animation)
            setAnimationState(newState - animation.getLength());

            // find the new animation
            animation = AnimationHandler::getAnimation(animation.getNextAnimation());
        } else {

            // iterate object->animation
            setAnimationState(newState);
        }
    }

// getters and setters

    Animation &DrawableMenu::getAnimation() const {
        return *m_currentAnimation;
    }

    seconds DrawableMenu::getAnimationState() const {
        return m_animationState;
    }

    RelPixel DrawableMenu::getTopLeft() const {
        return m_topLeft;
    }

    RelPixel DrawableMenu::getBottomRight() const {
        return m_bottomRight;
    }

    void DrawableMenu::setAnimation(Animation &animation) {
        m_currentAnimation = &animation;
    }

    void DrawableMenu::setAnimationState(seconds animationState) {
        m_animationState = animationState;
    }


    void DrawableMenu::setTopLeft(RelPixel topLeft) {
        m_topLeft = topLeft;
    }

    void DrawableMenu::setBottomRight(RelPixel bottomRight) {
        m_bottomRight = bottomRight;
    }

} // BattleRoom namespace

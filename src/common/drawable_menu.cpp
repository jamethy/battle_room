#include "battle_room/common/drawable_menu.h"
#include "battle_room/common/animation_handler.h"

namespace BattleRoom {

// apply settings

    void DrawableMenu::applySettings(ResourceDescriptor settings) {

        m_location.applySettings(settings.getSubResource("Location"));

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
            m_animationState(0) {}

// getters and setters

    Animation &DrawableMenu::getAnimation() const {
        return *m_currentAnimation;
    }

    seconds DrawableMenu::getAnimationState() const {
        return m_animationState;
    }

    Vector2D DrawableMenu::getLocation() const {
        return m_location;
    }

    void DrawableMenu::setAnimation(Animation &animation) {
        m_currentAnimation = &animation;
    }

    void DrawableMenu::setAnimationState(seconds animationState) {
        m_animationState = animationState;
    }

    void DrawableMenu::setLocation(Vector2D location) {
        m_location = location;
    }

} // BattleRoom namespace


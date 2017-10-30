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

        sub = settings.getSubResource("Width");
        if (isNotEmpty(sub.getValue())) {
            m_width = stod(sub.getValue());
        }

        sub = settings.getSubResource("Height");
        if (isNotEmpty(sub.getValue())) {
            m_height = stod(sub.getValue());
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
            m_width(1), 
            m_height(1)
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

    Vector2D DrawableMenu::getLocation() const {
        return m_location;
    }

    relpx DrawableMenu::getWidth() const {
        return m_width;
    }

    relpx DrawableMenu::getHeight() const {
        return m_height;
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

    void DrawableMenu::setWidth(relpx width) {
        m_width = width;
    }

    void DrawableMenu::setHeight(relpx height) {
        m_height = height;
    }

} // BattleRoom namespace


#ifndef ANIMATION_HANDLER_H
#define ANIMATION_HANDLER_H

#include "battle_room/common/animation.h"

namespace BattleRoom {

/**
 * key to get missing-animation animation
 */
    const std::string MISSING_ANIMATION = "missing_animation";

/**
 * Singleton class to handle retrieving animations via keys
 */
    class AnimationHandler {

    public:

        /**
         * \brief Gets the reference to the animation of the given key
         * \param Name of the animation to return (should be the filename without extension)
         * \return Reference to the animation desired or MISSING_ANIMATION if missing
         */
        static Animation &getAnimation(std::string animationKey);

    }; // AnimationHandler class
} // BattleRoom namespace
#endif // ANIMATION_HANDLER_H

#ifndef ANIMATION_HANDLER_H
#define ANIMATION_HANDLER_H

#include "battle_room/engine/animation/animation.h"

#include <string>
#include <unordered_map>

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

    // get the singleton instance
    // access other functions through this
    static AnimationHandler& get();

    /**
     * \brief Gets the reference to the animation of the given key
     * \param Name of the animation to return (should be the filename without extension)
     * \return Reference to the animation desired or MISSING_ANIMATION if missing
     */
    Animation& getAnimation(std::string animationKey);

    /**
     * \brief Sets the directory where animations can be found
     * This should be called before any animations are gotten
     *
     * \param Either relative or absolute path to resources
     */
    void setResourcePath(std::string resourcePath);

protected:

    std::string m_resourcePath; ///< Path to resources
    std::unordered_map<std::string,Animation> m_animationMap; ///< Animations mapped to keys

    // private constructor
    AnimationHandler();

}; // AnimationHandler class
} // BattleRoom namespace
#endif // ANIMATION_HANDLER_H

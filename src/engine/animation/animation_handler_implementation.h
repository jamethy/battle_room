#ifndef ANIMATION_HANDLER_IMPLEMENTATION_H
#define ANIMATION_HANDLER_IMPLEMENTATION_H

#include "battle_room/engine/animation/animation_handler.h"

#include <string>
#include <unordered_map>

namespace BattleRoom {

/**
 * See parent class
 */
class AnimationHandlerImplementation : public AnimationHandler {

public:

    // constructor
    AnimationHandlerImplementation();

    // inherited

    Animation& getAnimation(std::string animationKey) override;
    void setResourcePath(std::string resourcePath) override;

protected:

    std::string m_resourcePath; ///< Path to resources
    std::unordered_map<std::string,Animation> m_animationMap; ///< Animations mapped to keys

}; // AnimationHandlerImplementation class
} // BattleRoom namespace
#endif // ANIMATION_HANDLER_IMPLEMENTATION_H

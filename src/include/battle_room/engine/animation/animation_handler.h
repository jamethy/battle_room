#ifndef ANIMATION_HANDLER_H
#define ANIMATION_HANDLER_H

#include "battle_room/engine/animation/animation.h"

#include <string>
#include <unordered_map>

namespace BattleRoom {

const std::string MISSING_ANIMATION = "missing_animation";

class AnimationHandler {

public:

    AnimationHandler(std::string resourcePath);

    Animation& getAnimation(std::string animation);

private:

    std::string m_resourcePath;
    std::unordered_map<std::string,Animation> m_animationMap;

}; // AnimationHandler class
} // BattleRoom namespace
#endif // ANIMATION_HANDLER_H

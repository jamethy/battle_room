#ifndef ANIMATION_HANDLER_H
#define ANIMATION_HANDLER_H

#include "battle_room/engine/animation/animation.h"

#include <string>
#include <unordered_map>

namespace BattleRoom {

const std::string MISSING_ANIMATION = "missing_animation";

class AnimationHandler {

public:

    // get the singleton instance
    static AnimationHandler& get();

    Animation& getAnimation(std::string animation);

    void setResourcePath(std::string resourcePath);

protected:

    std::string m_resourcePath;
    std::unordered_map<std::string,Animation> m_animationMap;

    AnimationHandler();

}; // AnimationHandler class
} // BattleRoom namespace
#endif // ANIMATION_HANDLER_H

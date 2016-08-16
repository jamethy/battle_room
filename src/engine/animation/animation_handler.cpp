
#include "battle_room/engine/animation/animation_handler.h"

using std::string;

namespace BattleRoom {

AnimationHandler::AnimationHandler() 
{ }

AnimationHandler& AnimationHandler::get() {
    static AnimationHandler handler;
    return handler;
}

void AnimationHandler::setResourcePath(string resourcePath) {
    m_resourcePath = resourcePath;
    getAnimation(MISSING_ANIMATION);
}

Animation& AnimationHandler::getAnimation(string animation) {

    if (m_animationMap.count(animation) == 0) {
        string animationFilePath = m_resourcePath + "/" + animation + ".txt";
        ResourceDescriptor descriptor = ResourceDescriptor::readFile(animationFilePath);
        Animation anim(descriptor);

        if (anim.getImageFile().empty()) {
            m_animationMap.insert(
                    std::pair<string,Animation>(animation,m_animationMap.at(MISSING_ANIMATION))
            );
        }
        else {
            m_animationMap.insert(std::pair<string,Animation>(animation,anim));
        }
    }

    return m_animationMap.at(animation);
}

} // Animation namespace

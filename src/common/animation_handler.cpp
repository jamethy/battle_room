
#include "battle_room/common/animation_handler.h"

#include <unordered_map>

using std::string;

namespace BattleRoom {

std::string m_resourcePath; ///< Path to resources
std::unordered_map<std::string,Animation> m_animationMap; ///< Animations mapped to keys

// other functions

void AnimationHandler::setResourcePath(string resourcePath) {
    m_resourcePath = resourcePath;
    getAnimation(MISSING_ANIMATION);
}

Animation& AnimationHandler::getAnimation(string animation) {

    if (m_animationMap.count(animation) == 0) {
        string animationFilePath = m_resourcePath + "/" + animation + DESCRIPTOR_EXTENSION;
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

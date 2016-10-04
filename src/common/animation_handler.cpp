
#include "battle_room/common/animation_handler.h"
#include "battle_room/common/file_utils.h"

#include <unordered_map>

using std::string;

namespace BattleRoom {

std::unordered_map<std::string,Animation> m_animationMap; ///< Animations mapped to keys

Animation loadAnimation(string animationName) {

    string animationFilePath = getResourcePath() + "/animations/" 
        + animationName + DESCRIPTOR_EXTENSION;

    ResourceDescriptor descriptor = ResourceDescriptor::readFile(animationFilePath);
    return Animation(descriptor);
}

// other functions
Animation& AnimationHandler::getAnimation(string animation) {

    // if the animation is not in the map, load it
    if (m_animationMap.count(animation) == 0) {

        Animation anim = loadAnimation(animation);

        // If animation was unsuccessful in loading, place missing
        if (isEmpty(anim.getImageFile())) {

            // if missing animation hasn't been loaded yet, load it
            if (m_animationMap.count(MISSING_ANIMATION) == 0) {
                Animation missingAnim = loadAnimation(MISSING_ANIMATION);
                m_animationMap.insert(std::make_pair(MISSING_ANIMATION,missingAnim));
            }

            // Insert missing in place
            m_animationMap.insert(
                    std::pair<string,Animation>(animation,m_animationMap.at(MISSING_ANIMATION))
            );
        }

        // If animation was successful in loading, place it
        else {
            m_animationMap.insert(std::pair<string,Animation>(animation,anim));
        }
    }

    // return animaiton from map
    return m_animationMap.at(animation);
}

} // Animation namespace

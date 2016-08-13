
#include "battle_room/engine/animation/animation_handler.h"

using std::string;

namespace Animation {

AnimationHandler::AnimationHandler(string resourcePath) 
    : m_resourcePath(resourcePath)
{ }


Animation loadAnimation(string animationFilePath) {
    
}

Animation& AnimationHandler::getAnimation(string animation) {

    if (m_animationMap.count(animation) == 0) {
        Animation anm = loadAnimation loadAnimation(m_resourcePath + animation + ".txt");
        if (anm
        m_animationMap.insert(animation,
    }


}

} // Animation namespace

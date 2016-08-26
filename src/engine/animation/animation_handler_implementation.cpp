
#include "animation_handler_implementation.h"

using std::string;

namespace BattleRoom {

// constructor

AnimationHandler::AnimationHandler() 
{ }

AnimationHandlerImplementation::AnimationHandlerImplementation() 
{ }

// Getter for the singleton

AnimationHandler& AnimationHandler::get() {
    static AnimationHandlerImplementation handler;
    return handler;
}

// other functions

void AnimationHandlerImplementation::setResourcePath(string resourcePath) {
    m_resourcePath = resourcePath;
    getAnimation(MISSING_ANIMATION);
}

Animation& AnimationHandlerImplementation::getAnimation(string animation) {

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

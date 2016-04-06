#include "battleroom/AnimationService.h"

#include <unordered_map>

namespace Animations {

class ConcreteAnimationService
{

private:

    std::unordered_map<std::string,Animation> m_animations;
    AnimationService* getSingleton();
    
public:
    ConcreteAnimationService() {
        addAnimation(Animation("nullAnimation"));
    };

    Animation& nullAnimation(){ 
        return m_animations.at("nullAnimation");
    }

    void addAnimation(const Animation animation) {
        m_animations.emplace(animation.getName(),animation);
    }

    const Animation& getAnimation(const std::string& name) {
        auto animation = m_animations.find(name);
        if(animation == m_animations.end()) { 
            return nullAnimation();
        } else {
            return animation->second;
        }
    }

} globalAnimations;

////////////////////////////////////////////////////////////////////////////////
// Public Interface Functions
////////////////////////////////////////////////////////////////////////////////
AnimationService::AnimationService() { }

void AnimationService::addAnimation(const Animation animation) {
    globalAnimations.addAnimation(animation);
}

const Animation& AnimationService::getAnimation(const std::string& name) {
    return globalAnimations.getAnimation(name);
}

} // end Animations namespace

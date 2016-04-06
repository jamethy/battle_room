#include "battleroom/Animation.h"

namespace Animations {

Animation::Animation(const std::string& name) 
    : m_animationName(name) {
}

Animation::Animation(const Animation& other) 
    : m_animationName(other.m_animationName) {
}

std::string Animation::getName() const {
    return m_animationName;
}

} // end Animations namespace

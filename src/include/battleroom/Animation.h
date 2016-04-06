#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>

namespace Animations {

class Animation {

private:
    
    //std::vector<Frame> m_frames;
    //std::string m_nextAnimation;
    //std::string m_spriteFilename;
    std::string m_animationName;

public:

    Animation(const std::string& name);
    Animation(const Animation& other);
    std::string getName() const;

};

} // end Animations namespace
#endif // ANIMATION_H

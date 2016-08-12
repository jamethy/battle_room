#ifndef ANIMATION_H
#define ANIMATION_H

#include "battle_room/engine/animation/frame.h"

#include <string>
#include <vector>

namespace Animation {

class Animation {

public:

    Animation(std::string imageFile, std::string nextAnimation, std::vector<Frame> frames);

    const std::string& getImageFile();

    const std::string& getNextAnimation();

    const std::vector<Frame>& getFrames();

private:
    
    const std::string m_imageFile;
    
    const std::string m_nextAnimation;

    const std::vector<Frame> m_frames;


}; // Animation class

Animation& getDefaultAnimation();

} // Animation namespace
#endif // ANIMATION_H

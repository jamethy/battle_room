#ifndef ANIMATION_H
#define ANIMATION_H

#include "battle_room/engine/animation/frame.h"

#include <string>
#include <vector>

namespace Animation {

public:

    void setImageFile(std::string imageFile);

    void setNextAnimation(std::string nextAnimation);

    void setFrames(std::vector<Frame> frames);

    std::string getImageFile();

    std::string getNextAnimation();

    std::vector<Frame> getFrames();

private:
    
    std::string m_imageFile;
    
    std::string m_nextAnimation;

    std::vector<Frame> m_frames;


}; // Animation class
} // Animation namespace
#endif // ANIMATION_H

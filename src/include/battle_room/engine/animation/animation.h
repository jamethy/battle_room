#ifndef ANIMATION_H
#define ANIMATION_H

#include "battle_room/engine/animation/frame.h"
#include "battle_room/common/resource_descriptor.h"

#include <string>
#include <vector>

namespace BattleRoom {

class Animation {

public:

    Animation(ResourceDescriptor descriptor);

    const std::string& getImageFile();

    const std::string& getNextAnimation();

    const std::vector<Frame>& getFrames();

private:
    
    std::string m_imageFile;
    
    std::string m_nextAnimation;

    std::vector<Frame> m_frames;


}; // Animation class
} // BattleRoom namespace
#endif // ANIMATION_H

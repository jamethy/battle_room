#include "battle_room/engine/animation/animation.h"

#include <iostream>
#include <algorithm>

using std::string;
using std::vector;

namespace BattleRoom {

Animation::Animation(ResourceDescriptor descriptor) {

    ResourceDescriptor sub = descriptor.getSubResource("ImageFile");
    if (!sub.getKey().empty()) {
        m_imageFile = sub.getValue();
    } 

    sub = descriptor.getSubResource("NextAnimation");
    if (!sub.getKey().empty()) {
        m_nextAnimation = sub.getValue();
    } 

    vector<ResourceDescriptor> subs = descriptor.getSubResources("Frame");
    for (ResourceDescriptor& rd : subs) {
        m_frames.push_back(Frame(rd));
    }

    std::sort(m_frames.begin(), m_frames.end(), 
            [](const Frame& a, const Frame& b) {
                return b.getEndTime() > a.getEndTime();
        });

}

const string& Animation::getImageFile() {
    return m_imageFile;
}

const string& Animation::getNextAnimation() {
    return m_nextAnimation;
}

const vector<Frame>& Animation::getFrames() {
    return m_frames;
}

const Frame& Animation::getFrame(seconds animationState) {

    if (m_frames.size() == 0) {
        // throw exception
    }

    Frame& returnFrame = m_frames[0];
    for (const Frame& frame : m_frames) {
        if (animationState < frame.getEndTime()) {
            return frame;
        }
    }
    return m_frames.back();
}

} // BattleRoom namespace

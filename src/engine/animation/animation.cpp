#include "battle_room/engine/animation/animation.h"

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

} // BattleRoom namespace

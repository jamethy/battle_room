#include "battle_room/engine/animation/animation.h"

using std::string;
using std::vector;

namespace Animation {

Animation::Animation(string imageFile, string nextAnimation, vector<Frame> frames)
    : m_imageFile(imageFile), m_nextAnimation(nextAnimation), m_frames(frames)
{ }

const string& Animation::getImageFile() {
    return m_imageFile;
}

const string& Animation::getNextAnimation() {
    return m_nextAnimation;
}

const vector<Frame>& Animation::getFrames() {
    return m_frames;
}

} // Animation namespace

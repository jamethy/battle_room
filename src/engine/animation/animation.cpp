#include "battle_room/engine/animation/animation.h"

using std::string;
using std::vector;

namespace Animation {

void Animation::setImageFile(string imageFile) {
    m_imageFile = imageFile;
}

void Animation::setNextAnimation(string nextAnimation) {
    m_nextAnimation = nextAnimation;
}

void Animation::setFrames(vector<Frame> frames) {
    m_frames = frames;
}

string Animation::getImageFile() {
    return m_imageFile;
}

string Animation::getNextAnimation() {
    return m_nextAnimation;
}

vector<Frame> Animation::getFrames() {
    return m_frames;
}

} // Animation namespace

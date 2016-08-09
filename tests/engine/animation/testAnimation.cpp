
#include "battle_room/engine/animation/frame.h"
#include "battle_room/engine/animation/animation.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::string;
using std::vector;
using Common::Pixel;

namespace Animation {

TEST(Test_gen, typical) {

    
    Frame frame(0.1, Pixel(0,0), Pixel(100,100), 2.1, 2.3);

    vector<Frame> frames;
    frames.push_back(frame);
    frames.push_back(frame);

    Animation animation("image file", "next animation", frames);

    EXPECT_EQ(0.1, frame.getEndTime());
}

} // Animation namespace

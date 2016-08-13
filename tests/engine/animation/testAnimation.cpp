
#include "battle_room/engine/animation/frame.h"
#include "battle_room/engine/animation/animation.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::string;
using std::vector;

namespace BattleRoom {

TEST(Test_gen, typical) {

    ResourceDescriptor animationResource;

    vector<ResourceDescriptor> subResources;

    ResourceDescriptor frameResource;
    frameResource.setKey("Frame");
    ResourceDescriptor sub;
    sub.setKey("EndTime"); sub.setValue("0.1");
    subResources.push_back(sub);
    sub.setKey("TopRow"); sub.setValue("0");
    subResources.push_back(sub);
    sub.setKey("LeftCol"); sub.setValue("0");
    subResources.push_back(sub);
    sub.setKey("BottomRow"); sub.setValue("100");
    subResources.push_back(sub);
    sub.setKey("RightCol"); sub.setValue("100");
    subResources.push_back(sub);
    sub.setKey("XScale"); sub.setValue("2.1");
    subResources.push_back(sub);
    sub.setKey("YScale"); sub.setValue("2.3");
    subResources.push_back(sub);
    frameResource.setSubResources(subResources);

    subResources.clear();
    subResources.push_back(frameResource);
    subResources.push_back(frameResource);

    animationResource.setKey("animation");
    animationResource.setValue("txt");
    sub.setKey("ImageFile"); sub.setValue("image file");
    subResources.push_back(sub);
    sub.setKey("NextAnimation"); sub.setValue("next animation");
    subResources.push_back(sub);
    animationResource.setSubResources(subResources);
    
    Animation animation(animationResource);

    EXPECT_STREQ("image file", animation.getImageFile().c_str());
    EXPECT_STREQ("next animation", animation.getNextAnimation().c_str());
    ASSERT_EQ(2u, animation.getFrames().size());

    Frame frame = animation.getFrames()[0];
    EXPECT_EQ(0.1, frame.getEndTime());
    EXPECT_EQ(0, frame.getTopLeft().getRow());
    EXPECT_EQ(0, frame.getTopLeft().getCol());
    EXPECT_EQ(100, frame.getBottomRight().getRow());
    EXPECT_EQ(100, frame.getBottomRight().getCol());
    EXPECT_EQ(2.1, frame.getXScale());
    EXPECT_EQ(2.3, frame.getYScale());

    frame = animation.getFrames()[1];
    EXPECT_EQ(0.1, frame.getEndTime());
    EXPECT_EQ(0, frame.getTopLeft().getRow());
    EXPECT_EQ(0, frame.getTopLeft().getCol());
    EXPECT_EQ(100, frame.getBottomRight().getRow());
    EXPECT_EQ(100, frame.getBottomRight().getCol());
    EXPECT_EQ(2.1, frame.getXScale());
    EXPECT_EQ(2.3, frame.getYScale());
}

} // BattleRoom namespace

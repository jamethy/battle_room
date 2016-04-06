#include "battleroom/AnimationService.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace Animations {

TEST(Test_AnimationService_null, callForNull) {

    const Animation& null = AnimationService::getAnimation("nullAnimation");
    EXPECT_EQ( "nullAnimation", null.getName());
}

TEST(Test_AnimationService_null, getNull) {

    const Animation& null = AnimationService::getAnimation("lksdjf;laksdjf");
    EXPECT_EQ( "nullAnimation", null.getName());
}

TEST(Test_AnimationService_Adding, adding) {

    AnimationService::addAnimation(Animation("testAni"));
    const Animation& testAni = AnimationService::getAnimation("testAni");
    EXPECT_EQ( "testAni", testAni.getName());
}

} // end Animations namespace

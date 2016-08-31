
#include "battle_room/common/quaternion.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cmath>

namespace BattleRoom {

TEST(Test_applySettingsFromValue, typical) {

    std::vector<std::string> settingLines;
    settingLines.push_back("Quat: 1.1,2,3.3,4.4");

    unsigned start = 0;
    ResourceDescriptor settings;
    settings.fillFromInput(settingLines, start);

    Quaternion q;
    q.applySettings(settings);

    EXPECT_DOUBLE_EQ(1.1, q.w());
    EXPECT_DOUBLE_EQ(2.0, q.i());
    EXPECT_DOUBLE_EQ(3.3, q.j());
    EXPECT_DOUBLE_EQ(4.4, q.k());
}

// TODO write more useful tests...

TEST(Test_rotated, identity) {

    Vector3D x(1,2,3);
    Quaternion q(1,0,0,0);

    Vector3D xx = q.getRotated(x);

    EXPECT_DOUBLE_EQ(1, xx.x());
    EXPECT_DOUBLE_EQ(2, xx.y());
    EXPECT_DOUBLE_EQ(3, xx.z());
}

TEST(Test_rotated, ninetyAboutY) {

    Vector3D x(1,0,0);
    Quaternion q(std::sqrt(0.5),0,std::sqrt(0.5),0);

    Vector3D xx = q.getRotated(x);

    EXPECT_DOUBLE_EQ(0, xx.x());
    EXPECT_DOUBLE_EQ(0, xx.y());
    EXPECT_DOUBLE_EQ(-1, xx.z());
}

TEST(Test_rotated, ninetyAboutXY) {

    Vector3D x(1,0,0);
    Quaternion q(0.5,0.5,0.5,0.5);

    Vector3D xx = q.getRotated(x);

    EXPECT_DOUBLE_EQ(0, xx.x());
    EXPECT_DOUBLE_EQ(1, xx.y());
    EXPECT_DOUBLE_EQ(0, xx.z());
}


} // BattleRoom namespace

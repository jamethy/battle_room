
#include "battle_room/common/resource_descriptor.h"
#include "battle_room/common/file_utils.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>

using std::string;
using std::vector;

namespace BattleRoom {

// helper functions
void testFrameResource(ResourceDescriptor frame, string time, string toprow, string leftcol, string botrow, string rightcol) {

    EXPECT_STREQ("Frame", frame.getKey().c_str());
    EXPECT_STREQ("", frame.getValue().c_str());
    vector<ResourceDescriptor> subs = frame.getSubResources();
    ASSERT_EQ(7u, subs.size());

    EXPECT_STREQ("EndTime", subs[0].getKey().c_str());
    EXPECT_STREQ(time.c_str(), subs[0].getValue().c_str());
    EXPECT_EQ(0u, subs[0].getSubResources().size());

    EXPECT_STREQ("TopRow", subs[1].getKey().c_str());
    EXPECT_STREQ(toprow.c_str(), subs[1].getValue().c_str());
    EXPECT_EQ(0u, subs[1].getSubResources().size());

    EXPECT_STREQ("LeftCol", subs[2].getKey().c_str());
    EXPECT_STREQ(leftcol.c_str(), subs[2].getValue().c_str());
    EXPECT_EQ(0u, subs[2].getSubResources().size());


    EXPECT_STREQ("BottomRow", subs[3].getKey().c_str());
    EXPECT_STREQ(botrow.c_str(), subs[3].getValue().c_str());
    EXPECT_EQ(0u, subs[3].getSubResources().size());

    EXPECT_STREQ("RightCol", subs[4].getKey().c_str());
    EXPECT_STREQ(rightcol.c_str(), subs[4].getValue().c_str());
    EXPECT_EQ(0u, subs[4].getSubResources().size());

    EXPECT_STREQ("XScale", subs[5].getKey().c_str());
    EXPECT_STREQ("1", subs[5].getValue().c_str());
    EXPECT_EQ(0u, subs[5].getSubResources().size());

    EXPECT_STREQ("YScale", subs[6].getKey().c_str());
    EXPECT_STREQ("1", subs[6].getValue().c_str());
    EXPECT_EQ(0u, subs[6].getSubResources().size());
}

TEST(Test_fillFromInput, testFile) {

    string test_file = string(TEST_FILES_DIR) + "/test_animation.txt";
    ResourceDescriptor rd = ResourceDescriptor::readFile(test_file);

    EXPECT_STREQ("test_animation", rd.getKey().c_str());
    EXPECT_STREQ("txt", rd.getValue().c_str());

    vector<ResourceDescriptor> level1 = rd.getSubResources();
    ASSERT_EQ(7u,level1.size());

    ResourceDescriptor sub1 = level1[0];
    vector<ResourceDescriptor> level2 = sub1.getSubResources();

    EXPECT_STREQ("ImageFile", sub1.getKey().c_str());
    EXPECT_STREQ("test_animation.jpg", sub1.getValue().c_str());
    EXPECT_EQ(0u,level2.size());

    sub1 = level1[1];
    level2 = sub1.getSubResources();

    EXPECT_STREQ("NextAnimation", sub1.getKey().c_str());
    EXPECT_STREQ("test_animation", sub1.getValue().c_str());
    EXPECT_EQ(0u,level2.size());


    testFrameResource(level1[2],"0.2","213","81","1150","500");
    testFrameResource(level1[3],"0.3","213","500","1150","944");
    testFrameResource(level1[4],"0.4","213","944","1150","1344");
    testFrameResource(level1[5],"0.5","213","1344","1150","1780");
    testFrameResource(level1[6],"0.6","213","1780","1150","2260");
}

TEST(Test_filter, testFile) {

    string test_file = string(TEST_FILES_DIR) + "/test_animation.txt";
    ResourceDescriptor rd = ResourceDescriptor::readFile(test_file);

    vector<ResourceDescriptor> frames = rd.getSubResources("Frame");

    EXPECT_EQ(5u, frames.size());
}

TEST(Test_getSub, testFile) {

    string test_file = string(TEST_FILES_DIR) + "/test_animation.txt";
    ResourceDescriptor rd = ResourceDescriptor::readFile(test_file);

    ResourceDescriptor sub = rd.getSubResource("ImageFile");
    EXPECT_STREQ("ImageFile", sub.getKey().c_str());
    EXPECT_STREQ("test_animation.jpg", sub.getValue().c_str());

    sub = rd.getSubResource("NextAnimation");
    EXPECT_STREQ("NextAnimation", sub.getKey().c_str());
    EXPECT_STREQ("test_animation", sub.getValue().c_str());
}

} // BattleRoom namespace

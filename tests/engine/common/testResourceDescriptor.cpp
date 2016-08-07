
#include "battle_room/engine/common/resource_descriptor.h"
#include "battle_room/engine/common/file_utils.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>

using std::string;
using std::vector;

namespace Common {

// helper functions
void testFrameResource(ResourceDescriptor frame, string time, string toprow, string leftcol, string botrow, string rightcol) {

    EXPECT_EQ("Frame", frame.getKey());
    EXPECT_EQ("", frame.getValue());
    vector<ResourceDescriptor> subs = frame.getSubResources();
    EXPECT_EQ(7u, subs.size());

    EXPECT_EQ("EndTime", subs[0].getKey());
    EXPECT_EQ(time, subs[0].getValue());
    EXPECT_EQ(0u, subs[0].getSubResources().size());

    EXPECT_EQ("TopRow", subs[1].getKey());
    EXPECT_EQ(toprow, subs[1].getValue());
    EXPECT_EQ(0u, subs[1].getSubResources().size());

    EXPECT_EQ("LeftCol", subs[2].getKey());
    EXPECT_EQ(leftcol, subs[2].getValue());
    EXPECT_EQ(0u, subs[2].getSubResources().size());


    EXPECT_EQ("BottomRow", subs[3].getKey());
    EXPECT_EQ(botrow, subs[3].getValue());
    EXPECT_EQ(0u, subs[3].getSubResources().size());

    EXPECT_EQ("RightCol", subs[4].getKey());
    EXPECT_EQ(rightcol, subs[4].getValue());
    EXPECT_EQ(0u, subs[4].getSubResources().size());

    EXPECT_EQ("XScale", subs[5].getKey());
    EXPECT_EQ("1", subs[5].getValue());
    EXPECT_EQ(0u, subs[5].getSubResources().size());

    EXPECT_EQ("YScale", subs[6].getKey());
    EXPECT_EQ("1", subs[6].getValue());
    EXPECT_EQ(0u, subs[6].getSubResources().size());
}

TEST(Test_fillFromInput, testFile) {
    string test_file = string(TEST_FILES_DIR) + "/test_animation.txt";
    vector<string> lines = readEntireFile(test_file);

    ResourceDescriptor rd;
    unsigned start = 0;
    rd.fillFromInput(lines,start);

    EXPECT_EQ("test_animation", rd.getKey());
    EXPECT_EQ("txt", rd.getValue());

    vector<ResourceDescriptor> level1 = rd.getSubResources();
    EXPECT_EQ(7u,level1.size());

    ResourceDescriptor sub1 = level1[0];
    vector<ResourceDescriptor> level2 = sub1.getSubResources();

    EXPECT_EQ("ImageFile", sub1.getKey());
    EXPECT_EQ("test_animation.jpg", sub1.getValue());
    EXPECT_EQ(0u,level2.size());

    sub1 = level1[1];
    level2 = sub1.getSubResources();

    EXPECT_EQ("NextAnimation", sub1.getKey());
    EXPECT_EQ("test_animation", sub1.getValue());
    EXPECT_EQ(0u,level2.size());

    testFrameResource(level1[2],"0.2","213","81","1150","500");
    testFrameResource(level1[3],"0.3","213","500","1150","944");
    testFrameResource(level1[4],"0.4","213","944","1150","1344");
    testFrameResource(level1[5],"0.5","213","1344","1150","1780");
    testFrameResource(level1[6],"0.6","213","1780","1150","2260");
}

} // Common namespace

#include "input_gatherer.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::vector;
using std::string;

namespace BattleRoom {

TEST(Test_inputGatherer, typical) {

    Input input;
    input.setKey(InputKey::A);
    input.setMotion(InputKey::PressedDown);
    input.addViewIntersection("intersection1", Vector3D(1,2,0));
    input.addViewIntersection("intersection2", Vector3D(2,3,0));
    InputGatherer::addInput(input);

    input.setKey(InputKey::MouseOnly);
    input.setMotion(InputKey::None);
    input.addViewIntersection("intersection3", Vector3D(1,3,0));
    input.addViewIntersection("intersection4", Vector3D(2,4,0));
    InputGatherer::addInput(input);

    Inputs inputsClass = InputGatherer::getAndClearInputs();

    // just because
    std::vector<Input> inputs;
    for (Input& input : inputsClass) {
        inputs.push_back(input);
    }

    ASSERT_EQ(2u, inputs.size());

    Input input1 = inputs[0];
    EXPECT_EQ(InputKey::A, input1.getKey());
    EXPECT_EQ(InputKey::PressedDown, input1.getMotion());

    ASSERT_TRUE(input1.containsView("intersection1"));
    Vector3D int1 = input1.getViewIntersection("intersection1");
    EXPECT_DOUBLE_EQ(1.0, int1.x());
    EXPECT_DOUBLE_EQ(2.0, int1.y());
    EXPECT_DOUBLE_EQ(0.0, int1.z());

    ASSERT_TRUE(input1.containsView("intersection2"));
    Vector3D int2 = input1.getViewIntersection("intersection2");
    EXPECT_DOUBLE_EQ(2.0, int2.x());
    EXPECT_DOUBLE_EQ(3.0, int2.y());
    EXPECT_DOUBLE_EQ(0.0, int2.z());

    Input input2 = inputs[1];
    EXPECT_EQ(InputKey::MouseOnly, input2.getKey());
    EXPECT_EQ(InputKey::None, input2.getMotion());

    ASSERT_TRUE(input2.containsView("intersection3"));
    Vector3D int3 = input2.getViewIntersection("intersection3");
    EXPECT_DOUBLE_EQ(1.0, int3.x());
    EXPECT_DOUBLE_EQ(3.0, int3.y());
    EXPECT_DOUBLE_EQ(0.0, int3.z());

    ASSERT_TRUE(input2.containsView("intersection4"));
    Vector3D int4 = input2.getViewIntersection("intersection4");
    EXPECT_DOUBLE_EQ(2.0, int4.x());
    EXPECT_DOUBLE_EQ(4.0, int4.y());
    EXPECT_DOUBLE_EQ(0.0, int4.z());
}

} // BattleRoom namespace

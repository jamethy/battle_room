#include "battle_room/engine/animation/camera.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::vector;
using std::string;

namespace BattleRoom {

TEST(Test_applySettings, typical) {

    vector<string> settings;
    settings.push_back("Camera:");
    settings.push_back("    Position:");
    settings.push_back("        Location:");
    settings.push_back("            X: 1.11");
    settings.push_back("            Y: 2.22");
    settings.push_back("            Z: 3.33");
    settings.push_back("        Orientation:");
    settings.push_back("            W: 1");
    settings.push_back("            I: 0");
    settings.push_back("            J: 0");
    settings.push_back("            K: 0");
    settings.push_back("    HorizontalFieldOfView: 1.8");
    settings.push_back("    VerticalFieldOfView: 1.3");
    settings.push_back("    Width: 200");
    settings.push_back("    Height: 100");

    unsigned int start = 0;
    ResourceDescriptor descriptor;
    descriptor.fillFromInput(settings, start);

    Camera camera;
    camera.applySettings(descriptor);

    Vector3D location = camera.getPosition().getLocation();
    Quaternion orientation = camera.getPosition().getOrientation();
    
    EXPECT_DOUBLE_EQ(1.11, location.x());
    EXPECT_DOUBLE_EQ(2.22, location.y());
    EXPECT_DOUBLE_EQ(3.33, location.z());

    EXPECT_DOUBLE_EQ(1.0, orientation.w());
    EXPECT_DOUBLE_EQ(0.0, orientation.i());
    EXPECT_DOUBLE_EQ(0.0, orientation.j());
    EXPECT_DOUBLE_EQ(0.0, orientation.k());

    EXPECT_DOUBLE_EQ(1.8, camera.getHorizontalFov());
    EXPECT_DOUBLE_EQ(1.3, camera.getVerticalFov());

    EXPECT_DOUBLE_EQ(200, camera.getWidth());
    EXPECT_DOUBLE_EQ(100, camera.getHeight());
}

} // BattleRoom namespace

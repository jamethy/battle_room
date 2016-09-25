#include "battle_room/graphics/camera.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::vector;
using std::string;

namespace BattleRoom {

TEST(Test_applySettings, typical) {

    ResourceDescriptor descriptor({
                "Camera:",
                "    Location: 1.11,2.22,3.33",
                "    Orientation:",
                "        W: 1",
                "        I: 0",
                "        J: 0",
                "        K: 0",
    });

    Camera camera;
    camera.applySettings(descriptor);

    Vector3D location = camera.getLocation();
    Quaternion orientation = camera.getOrientation();
    
    EXPECT_DOUBLE_EQ(1.11, location.x());
    EXPECT_DOUBLE_EQ(2.22, location.y());
    EXPECT_DOUBLE_EQ(3.33, location.z());

    EXPECT_DOUBLE_EQ(1.0, orientation.w());
    EXPECT_DOUBLE_EQ(0.0, orientation.i());
    EXPECT_DOUBLE_EQ(0.0, orientation.j());
    EXPECT_DOUBLE_EQ(0.0, orientation.k());
}

TEST(Test_fromLocation, straight_down) {

    ResourceDescriptor descriptor({
                "Camera:",
                "    Location: 0,0,2",
                "    Width: 250",
                "    Height: 150"
    });

    Camera camera;
    camera.applySettings(descriptor);
    camera.setHorizontalFov(0.785039);
    camera.setVerticalFov(0.785039);

    RelPixel p = camera.fromLocation(Vector3D(0,0,0));
    EXPECT_DOUBLE_EQ(0.5, p.getCol());
    EXPECT_DOUBLE_EQ(0.5, p.getRow());

    p = camera.fromLocation(Vector3D(0.828005,0,0));
    EXPECT_NEAR(1.0, p.getCol(),0.01);
    EXPECT_NEAR(0.5, p.getRow(),0.01);

    p = camera.fromLocation(Vector3D(-0.414002,0,0));
    EXPECT_NEAR(0.25, p.getCol(),0.01);
    EXPECT_NEAR(0.5, p.getRow(),0.01);

    p = camera.fromLocation(Vector3D(0,-0.414002,0));
    EXPECT_NEAR(0.5, p.getCol(),0.01);
    EXPECT_NEAR(0.75, p.getRow(),0.01);
}

TEST(Test_fromLocation, yawed_straight_down) {

    ResourceDescriptor descriptor(std::vector<std::string>({
                "Camera:",
                "    Location: 0,0,2"
    }));

    Camera camera;
    camera.applySettings(descriptor);
    camera.setHorizontalFov(0.785039);
    camera.setVerticalFov(0.785039);

    camera.rotateCounterClockwise(45*3.14156/180.0);

    RelPixel p = camera.fromLocation(Vector3D(0,0,0));
    EXPECT_NEAR(0.5, p.getCol(),0.01);
    EXPECT_NEAR(0.5, p.getRow(),0.01);

}

// Waiting on skewed textures
//TEST(Test_fromLocation, tiltedup) {
//
//    vector<string> settings;
//    settings.push_back("Camera:");
//    settings.push_back("    Position:");
//    settings.push_back("        Location:");
//    settings.push_back("            X: 0");
//    settings.push_back("            Y: 0");
//    settings.push_back("            Z: 2");
//    settings.push_back("        Orientation:");
//    settings.push_back("            W: 1");
//    settings.push_back("            I: 0");
//    settings.push_back("            J: 0");
//    settings.push_back("            K: 0");
//    settings.push_back("    HorizontalFieldOfView: 0.785039");
//    settings.push_back("    VerticalFieldOfView: 0.785039");
//    settings.push_back("    Width: 250");
//    settings.push_back("    Height: 150");
//
//    unsigned int start = 0;
//    ResourceDescriptor descriptor;
//    descriptor.fillFromInput(settings, start);
//
//    Camera camera;
//    camera.applySettings(descriptor);
//
//    camera.rotateUpDown(22.5*3.1415926/180.0);
//
//    RelPixel p = camera.fromLocation(Vector3D(0,0,0));
//    EXPECT_NEAR(0.5, p.getCol(),0.1);
//    EXPECT_NEAR(1.0, p.getRow(),0.1);
//
//    p = camera.fromLocation(Vector3D(0.76498,0,0));
//    EXPECT_NEAR(1.0, p.getCol(),0.1);
//    EXPECT_NEAR(1.0, p.getRow(),0.1);
//}
} // BattleRoom namespace

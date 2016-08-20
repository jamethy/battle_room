#include "battle_room/engine/animation/camera.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::vector;
using std::string;

namespace BattleRoom {

TEST(Test_rotate, typical) {

    Camera cam;

    std::cout << "Rotate clockwise by 45\n";
    cam.rotateClockwise(45.0*3.14156/180.0);

}

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

TEST(Test_fromLocation, straight_down) {

    vector<string> settings;
    settings.push_back("Camera:");
    settings.push_back("    Position:");
    settings.push_back("        Location:");
    settings.push_back("            X: 0");
    settings.push_back("            Y: 0");
    settings.push_back("            Z: 2");
    settings.push_back("        Orientation:");
    settings.push_back("            W: 1");
    settings.push_back("            I: 0");
    settings.push_back("            J: 0");
    settings.push_back("            K: 0");
    settings.push_back("    HorizontalFieldOfView: 0.785039");
    settings.push_back("    VerticalFieldOfView: 0.785039");
    settings.push_back("    Width: 250");
    settings.push_back("    Height: 150");

    unsigned int start = 0;
    ResourceDescriptor descriptor;
    descriptor.fillFromInput(settings, start);

    Camera camera;
    camera.applySettings(descriptor);

    Pixel p = camera.fromLocation(Vector3D(0,0,0));
    EXPECT_DOUBLE_EQ(125, p.getCol());
    EXPECT_DOUBLE_EQ(75, p.getRow());

    p = camera.fromLocation(Vector3D(0.828005,0,0));
    EXPECT_NEAR(250, p.getCol(),0.01);
    EXPECT_NEAR(75, p.getRow(),0.01);

    p = camera.fromLocation(Vector3D(-0.414002,0,0));
    EXPECT_NEAR(62.5, p.getCol(),0.01);
    EXPECT_NEAR(75, p.getRow(),0.01);

    p = camera.fromLocation(Vector3D(0,-0.414002,0));
    EXPECT_NEAR(125, p.getCol(),0.01);
    EXPECT_NEAR(112.5, p.getRow(),0.01);
}

TEST(Test_fromLocation, yawed_straight_down) {

    vector<string> settings;
    settings.push_back("Camera:");
    settings.push_back("    Position:");
    settings.push_back("        Location:");
    settings.push_back("            X: 0");
    settings.push_back("            Y: 0");
    settings.push_back("            Z: 2");
    settings.push_back("        Orientation:");
    settings.push_back("            W: 1");
    settings.push_back("            I: 0");
    settings.push_back("            J: 0");
    settings.push_back("            K: 0");
    settings.push_back("    HorizontalFieldOfView: 0.785039");
    settings.push_back("    VerticalFieldOfView: 0.785039");
    settings.push_back("    Width: 250");
    settings.push_back("    Height: 150");

    unsigned int start = 0;
    ResourceDescriptor descriptor;
    descriptor.fillFromInput(settings, start);

    Camera camera;
    camera.applySettings(descriptor);

    camera.rotateClockwise(45*3.14156/180.0);

    Pixel p = camera.fromLocation(Vector3D(0,0,0));
    EXPECT_NEAR(125, p.getCol(),0.01);
    EXPECT_NEAR(75, p.getRow(),0.01);

}

TEST(Test_fromLocation, tiltedup) {

    vector<string> settings;
    settings.push_back("Camera:");
    settings.push_back("    Position:");
    settings.push_back("        Location:");
    settings.push_back("            X: 0");
    settings.push_back("            Y: 0");
    settings.push_back("            Z: 2");
    settings.push_back("        Orientation:");
    settings.push_back("            W: 1");
    settings.push_back("            I: 0");
    settings.push_back("            J: 0");
    settings.push_back("            K: 0");
    settings.push_back("    HorizontalFieldOfView: 0.785039");
    settings.push_back("    VerticalFieldOfView: 0.785039");
    settings.push_back("    Width: 250");
    settings.push_back("    Height: 150");

    unsigned int start = 0;
    ResourceDescriptor descriptor;
    descriptor.fillFromInput(settings, start);

    Camera camera;
    camera.applySettings(descriptor);

    std::cout << "rotated up 22.5\n";
    camera.rotateUpDown(22.5*3.1415926/180.0);

    Pixel p = camera.fromLocation(Vector3D(0,0,0));
    EXPECT_NEAR(125, p.getCol(),0.1);
    EXPECT_NEAR(150, p.getRow(),0.1);

    p = camera.fromLocation(Vector3D(0.76498,0,0));
    EXPECT_NEAR(250, p.getCol(),0.1);
    EXPECT_NEAR(150, p.getRow(),0.1);
}
} // BattleRoom namespace

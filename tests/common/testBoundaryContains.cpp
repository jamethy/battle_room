#include "battle_room/common/boundary_set.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace BattleRoom {

TEST(Test_empty, typical) {

    ResourceDescriptor settings;
    UniqueBoundary boundary = BoundarySet::createBoundary(settings);

    // center
    EXPECT_FALSE( boundary->contains( Vector2D(0,0) ) );

    // somewhere on x/y
    EXPECT_FALSE( boundary->contains( Vector2D(4,0) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(0,8) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(7,6) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-4,0) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(0,-8) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(7,-6) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(15,0) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(0,18) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(2,10) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-15,0) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(2,-10) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(1230,32) ) );
}

TEST(Test_circle, typical) {

    ResourceDescriptor settings({
            "Boundary: Circle",
            "    Radius: 10",
            ""
    });

    UniqueBoundary boundary = BoundarySet::createBoundary(settings);

    // center of circle
    EXPECT_TRUE( boundary->contains( Vector2D(0,0) ) );

    // somewhere on x/y
    EXPECT_TRUE( boundary->contains( Vector2D(4,0) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(0,8) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(7,6) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(-4,0) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(0,-8) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(7,-6) ) );

    // outside
    EXPECT_FALSE( boundary->contains( Vector2D(15,0) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(0,18) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(2,10) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-15,0) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(2,-10) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(1230,32) ) );
}

TEST(Test_box, typical) {

    ResourceDescriptor settings({
            "Boundary: Box",
            "    Width: 3",
            "    Height: 10"
    });

    UniqueBoundary boundary = BoundarySet::createBoundary(settings);

    // center
    EXPECT_TRUE( boundary->contains( Vector2D(0,0) ) );

    // somewhere on x/y
    EXPECT_TRUE( boundary->contains( Vector2D(1,0) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(0,4) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(1.2,3) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(-1,0) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(0,-4) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(-1.2,-3) ) );

    // outside
    EXPECT_FALSE( boundary->contains( Vector2D(15,2) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(1,18) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-15,2) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(1,-18) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(20,30) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-22,20) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-12,-34) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(4,-9) ) );
}

TEST(Test_box, ninety) {

    ResourceDescriptor settings({
            "Boundary: Box",
            "    Width: 10",
            "    Height: 3",
            "    DegRotation: 90"
    });

    UniqueBoundary boundary = BoundarySet::createBoundary(settings);

    // center
    EXPECT_TRUE( boundary->contains( Vector2D(0,0) ) );

    // somewhere on x/y
    EXPECT_TRUE( boundary->contains( Vector2D(1,0) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(0,4) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(1.2,3) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(-1,0) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(0,-4) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(-1.2,-3) ) );

    // outside
    EXPECT_FALSE( boundary->contains( Vector2D(15,2) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(1,18) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-15,2) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(1,-18) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(20,30) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-22,20) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-12,-34) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(4,-9) ) );
}

TEST(Test_box, oneEighty) {

    ResourceDescriptor settings({
            "Boundary: Box",
            "    Width: 3",
            "    Height: 10",
            "    DegRotation: 180"
    });

    UniqueBoundary boundary = BoundarySet::createBoundary(settings);

    // center
    EXPECT_TRUE( boundary->contains( Vector2D(0,0) ) );

    // somewhere on x/y
    EXPECT_TRUE( boundary->contains( Vector2D(1,0) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(0,4) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(1.2,3) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(-1,0) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(0,-4) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(-1.2,-3) ) );

    // outside
    EXPECT_FALSE( boundary->contains( Vector2D(15,2) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(1,18) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-15,2) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(1,-18) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(20,30) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-22,20) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-12,-34) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(4,-9) ) );
}

TEST(Test_box, rotated) {

    ResourceDescriptor settings({
            "Boundary: Box",
            "    Width: 6",
            "    Height: 11",
            "    DegRotation: 30"
    });

    UniqueBoundary boundary = BoundarySet::createBoundary(settings);

    // somewhere on x/y
    EXPECT_TRUE( boundary->contains( Vector2D(3.4,0) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(0,5.9) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(2.5,1.45) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(-2.5,-1.45) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(-3.4,0) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(0,-5.9) ) );

    // outside
    EXPECT_FALSE( boundary->contains( Vector2D(3.5,0) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(0,6.1) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(2.6,1.5) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-2.6,-1.5) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-3.5,0) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-3.5,6.4) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(0,-6.1) ) );
}

TEST(Test_box, rotatedAndOffset) {

    ResourceDescriptor settings({
            "Boundary: Box",
            "    Width: 6",
            "    Height: 11",
            "    DegRotation: 30",
            "    Center: 1,2"
    });

    UniqueBoundary boundary = BoundarySet::createBoundary(settings);

    // somewhere on x/y
    EXPECT_TRUE( boundary->contains( Vector2D(4.4,2) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(1,7.9) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(3.5,3.45) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(-1.5,0.45) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(-2.4,2) ) );
    EXPECT_TRUE( boundary->contains( Vector2D(1,-3.9) ) );

    // outside
    EXPECT_FALSE( boundary->contains( Vector2D(4.5,2) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(1,8.1) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(3.6,3.5) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-1.6,0.5) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-2.5,2) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(-2.5,8.1) ) );
    EXPECT_FALSE( boundary->contains( Vector2D(1,-4.1) ) );
}

} // BattleRoom namespace

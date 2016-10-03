#include "battle_room/common/boundary_factory.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace BattleRoom {

TEST(Test_circle_circle, typical) {

    ResourceDescriptor settings1({
            "Boundary: Circle",
            "    Radius: 10",
            ""
    });

    ResourceDescriptor settings2({
            "Boundary: Circle",
            "    Radius: 6",
            ""
    });

    UniqueBoundary boundary1 = BoundaryFactory::createBoundary(settings1);
    UniqueBoundary boundary2 = BoundaryFactory::createBoundary(settings2);

    // general intersecting point, from both boundaries
    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D(0,0), 0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D(0,0), 0) );
    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D( 5, 3), 0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D(-5,-3), 0) );

    // mirror of above point (works because it's a circle...)
    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D(-5,-3), 0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D( 5, 3), 0) );

    // general non intersecting point
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(15,6), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-15,-6), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(-15,-6), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(15,6), 0) );
}


TEST(Test_circle_empty, typical) {

    ResourceDescriptor settings1({
            "Boundary: Circle",
            "    Radius: 10",
            ""
    });

    ResourceDescriptor settings2;

    UniqueBoundary boundary1 = BoundaryFactory::createBoundary(settings1);
    UniqueBoundary boundary2 = BoundaryFactory::createBoundary(settings2);

    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(0,0), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(0,0), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D( 5, 3), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-5,-3), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(-5,-3), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D( 5, 3), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(10,6), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-10,-6), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(-10,-6), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(10,6), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(9,8), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-9,-8), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(-9,-8), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(9,8), 0) );
}


TEST(Test_box_empty, typical) {

    ResourceDescriptor settings1({
            "Boundary: Box",
            "    Width: 5",
            "    Height: 10"
    });

    ResourceDescriptor settings2;

    UniqueBoundary boundary1 = BoundaryFactory::createBoundary(settings1);
    UniqueBoundary boundary2 = BoundaryFactory::createBoundary(settings2);

    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D( 0, 0), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D( 0, 0), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D( 3.9, 0), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(-3.9, 0), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D( 3.9, 0), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-3.9, 0), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(0, 8.4), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(0,-8.4), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(0, 8.4), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(0,-8.4), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(3,7.4), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-2,8), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-3,-3), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D( 4.1, 0), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(-4.1, 0), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D( 4.1, 0), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-4.1, 0), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(0, 8.6), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(0,-8.6), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(0, 8.6), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(0,-8.6), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-1, 9), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-5, -9), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(5, 8), 0) );
}


TEST(Test_box_box, unrotated) {

    ResourceDescriptor settings1({
            "Boundary: Box",
            "    Width: 5",
            "    Height: 10"
    });

    ResourceDescriptor settings2({
            "Boundary: Box",
            "    Width: 3",
            "    Height: 7"
    });

    UniqueBoundary boundary1 = BoundaryFactory::createBoundary(settings1);
    UniqueBoundary boundary2 = BoundaryFactory::createBoundary(settings2);

    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D( 0, 0), 0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D( 0, 0), 0) );

    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D( 3.9, 0), 0) );
    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D(-3.9, 0), 0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D( 3.9, 0), 0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D(-3.9, 0), 0) );

    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D(0, 8.4), 0) );
    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D(0,-8.4), 0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D(0, 8.4), 0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D(0,-8.4), 0) );

    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D(3,7.4), 0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D(-2,8), 0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D(-3,-3), 0) );

    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D( 4.1, 0), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(-4.1, 0), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D( 4.1, 0), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-4.1, 0), 0) );

    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(0, 8.6), 0) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(0,-8.6), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(0, 8.6), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(0,-8.6), 0) );

    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-1, 9), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-5, -9), 0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(5, 8), 0) );
}


TEST(Test_box_box, rotated) {

    ResourceDescriptor settings1({
            "Boundary: Box",
            "    Width: 5",
            "    Height: 10"
    });

    ResourceDescriptor settings2({
            "Boundary: Box",
            "    Width: 3",
            "    Height: 7"
    });

    double angle = toRadians(30.0);

    UniqueBoundary boundary1 = BoundaryFactory::createBoundary(settings1);
    UniqueBoundary boundary2 = BoundaryFactory::createBoundary(settings2);

    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D( 0, 0), angle) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D( 0, 0),-angle) );

    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D( 5.5, 0), angle) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D( 5.6, 0), angle) );

    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D( 4.2, 5), angle) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D( 4.3, 5), angle) );
    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D( 4.23, 4), angle) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D( 4.23, 6), angle) );

    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D( 3.9, 8.4), angle) );
}

TEST(Test_box_circle, unrotated) {

    ResourceDescriptor settings1({
            "Boundary: Box",
            "    Width: 5",
            "    Height: 10"
    });

    ResourceDescriptor settings2({
            "Boundary: Circle",
            "    Radius: 3",
            ""
    });

    UniqueBoundary boundary1 = BoundaryFactory::createBoundary(settings1);
    UniqueBoundary boundary2 = BoundaryFactory::createBoundary(settings2);

    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D( 0, 0),0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D( 0, 0),0) );

    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D( 2.4, 4.9),0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D(-2.4,-4.9),0) );
    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D( 2.6, 5.1),0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D(-2.6,-5.1),0) );

    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D( 2.4, 8.1),0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-2.4,-8.1),0) );
    
    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D( 5.4, 0),0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D(-5.4, 0),0) );

    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D( 5.6, 0),0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(-5.6, 0),0) );
    
    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D( 0, 7.9),0) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D( 0,-7.9),0) );

    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D(0, 8.1),0) );
    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(0,-8.1),0) );
}


TEST(Test_box_circle, rotated) {

    ResourceDescriptor settings1({
            "Boundary: Box",
            "    Width: 5",
            "    Height: 10"
    });

    ResourceDescriptor settings2({
            "Boundary: Circle",
            "    Radius: 3",
            ""
    });

    double angle = toRadians(30.0);

    UniqueBoundary boundary1 = BoundaryFactory::createBoundary(settings1);
    UniqueBoundary boundary2 = BoundaryFactory::createBoundary(settings2);

    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D( 0, 0),angle) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D( 0, 0),-angle) );

    EXPECT_TRUE( boundary1->intersects(boundary2.get(), Vector2D( 5.4, 5),angle) );
    EXPECT_FALSE( boundary1->intersects(boundary2.get(), Vector2D( 5.6, 5),angle) );

    EXPECT_FALSE( boundary2->intersects(boundary1.get(), Vector2D(4.77, 2.75), angle) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D(4.76, 2.75), angle) );
    EXPECT_TRUE( boundary2->intersects(boundary1.get(), Vector2D(4.76, 2.75), 0) );
}

} // BattleRoom namespace

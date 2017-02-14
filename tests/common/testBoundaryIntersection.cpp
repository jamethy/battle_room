#include "battle_room/common/boundary_set.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace BattleRoom {

void assertMtv(SatIntersection intr, Vector2D u) {
    EXPECT_TRUE(intr.doesIntersect());
    EXPECT_NEAR(intr.getMinTranslationUnitVector().x()*intr.getMinTranslationMagnitude(), u.x(), 0.001);
    EXPECT_NEAR(intr.getMinTranslationUnitVector().y()*intr.getMinTranslationMagnitude(), u.y(), 0.001);
}

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

    UniqueBoundary boundary1 = BoundarySet::createBoundary(settings1);
    UniqueBoundary boundary2 = BoundarySet::createBoundary(settings2);

    // general intersecting point, from both boundaries
    SatIntersection intersection = boundary1->intersects(boundary2.get(), Vector2D(0,0), 0);
    assertMtv(intersection, Vector2D(16,0));

    intersection = boundary2->intersects(boundary1.get(), Vector2D(0,0), 0);
    assertMtv(intersection, Vector2D(16,0));

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 5, 3), 0);
    assertMtv(intersection, Vector2D(8.7198868114, 5.23193208684));

    intersection = boundary2->intersects(boundary1.get(), Vector2D(-5,-3), 0);
    assertMtv(intersection, Vector2D(-8.7198868114, -5.23193208684));

    // mirror of above point (works because it's a circle...)
    intersection = boundary1->intersects(boundary2.get(), Vector2D(-5,-3), 0);
    assertMtv(intersection, Vector2D(-8.7198868114, -5.23193208684));

    intersection = boundary2->intersects(boundary1.get(), Vector2D( 5, 3), 0);
    assertMtv(intersection, Vector2D(8.7198868114, 5.23193208684));

    // general non intersecting point
    intersection = boundary1->intersects(boundary2.get(), Vector2D(15,6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(-15,-6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D(-15,-6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(15,6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
}


TEST(Test_circle_empty, typical) {

    ResourceDescriptor settings1({
            "Boundary: Circle",
            "    Radius: 10",
            ""
    });

    ResourceDescriptor settings2;

    UniqueBoundary boundary1 = BoundarySet::createBoundary(settings1);
    UniqueBoundary boundary2 = BoundarySet::createBoundary(settings2);

    SatIntersection intersection = boundary1->intersects(boundary2.get(), Vector2D(0,0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(0,0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D( 5, 3), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(-5,-3), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D(-5,-3), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D( 5, 3), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D(10,6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(-10,-6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D(-10,-6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(10,6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D(9,8), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(-9,-8), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D(-9,-8), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(9,8), 0);
    EXPECT_FALSE(intersection.doesIntersect());
}


TEST(Test_box_empty, typical) {

    ResourceDescriptor settings1({
            "Boundary: Box",
            "    Width: 5",
            "    Height: 10"
    });

    ResourceDescriptor settings2;

    UniqueBoundary boundary1 = BoundarySet::createBoundary(settings1);
    UniqueBoundary boundary2 = BoundarySet::createBoundary(settings2);

    SatIntersection intersection = boundary1->intersects(boundary2.get(), Vector2D( 0, 0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D( 0, 0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D( 3.9, 0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D(-3.9, 0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D( 3.9, 0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(-3.9, 0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D(0, 8.4), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D(0,-8.4), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(0, 8.4), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(0,-8.4), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(3,7.4), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(-2,8), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(-3,-3), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D( 4.1, 0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D(-4.1, 0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D( 4.1, 0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(-4.1, 0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D(0, 8.6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D(0,-8.6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(0, 8.6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(0,-8.6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(-1, 9), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(-5, -9), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(5, 8), 0);
    EXPECT_FALSE(intersection.doesIntersect());
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

    UniqueBoundary boundary1 = BoundarySet::createBoundary(settings1);
    UniqueBoundary boundary2 = BoundarySet::createBoundary(settings2);

    SatIntersection intersection = boundary1->intersects(boundary2.get(), Vector2D( 0, 0), 0);
    assertMtv(intersection, Vector2D(4, 0));
    intersection = boundary2->intersects(boundary1.get(), Vector2D( 0, 0), 0);
    assertMtv(intersection, Vector2D(4, 0));

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 3.9, 0), 0);
    assertMtv(intersection, Vector2D(0.1, 0));

    intersection = boundary1->intersects(boundary2.get(), Vector2D(-3.9, 0), 0);
    assertMtv(intersection, Vector2D(-0.1, 0));

    intersection = boundary2->intersects(boundary1.get(), Vector2D( 3.9, 0), 0);
    assertMtv(intersection, Vector2D(0.1, 0));

    intersection = boundary2->intersects(boundary1.get(), Vector2D(-3.9, 0), 0);
    assertMtv(intersection, Vector2D(-0.1, 0));

    intersection = boundary1->intersects(boundary2.get(), Vector2D(0, 8.4), 0);
    assertMtv(intersection, Vector2D(0, 0.1));

    intersection = boundary1->intersects(boundary2.get(), Vector2D(0,-8.4), 0);
    assertMtv(intersection, Vector2D(0, -0.1));

    intersection = boundary2->intersects(boundary1.get(), Vector2D(0, 8.4), 0);
    assertMtv(intersection, Vector2D(0, 0.1));

    intersection = boundary2->intersects(boundary1.get(), Vector2D(0,-8.4), 0);
    assertMtv(intersection, Vector2D(0, -0.1));

    intersection = boundary2->intersects(boundary1.get(), Vector2D(3,7.4), 0);
    assertMtv(intersection, Vector2D(1.0, 0));

    intersection = boundary2->intersects(boundary1.get(), Vector2D(-2,8), 0);
    assertMtv(intersection, Vector2D(0, 0.5));

    intersection = boundary2->intersects(boundary1.get(), Vector2D(-3,-3), 0);
    assertMtv(intersection, Vector2D(-1.0, 0));

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 4.1, 0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D(-4.1, 0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D( 4.1, 0), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(-4.1, 0), 0);
    EXPECT_FALSE(intersection.doesIntersect());

    intersection = boundary1->intersects(boundary2.get(), Vector2D(0, 8.6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D(0,-8.6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(0, 8.6), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(0,-8.6), 0);
    EXPECT_FALSE(intersection.doesIntersect());

    intersection = boundary2->intersects(boundary1.get(), Vector2D(-1, 9), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(-5, -9), 0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(5, 8), 0);
    EXPECT_FALSE(intersection.doesIntersect());
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

    UniqueBoundary boundary1 = BoundarySet::createBoundary(settings1);
    UniqueBoundary boundary2 = BoundarySet::createBoundary(settings2);

    SatIntersection intersection = boundary1->intersects(boundary2.get(), Vector2D( 0, 0), angle);
    assertMtv(intersection, Vector2D(5.549, 0));

    intersection = boundary2->intersects(boundary1.get(), Vector2D( 0, 0),-angle);
    assertMtv(intersection, Vector2D(4.806, -2.7745));

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 5.5, 0), angle);
    assertMtv(intersection, Vector2D(0.049, 0));

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 5.6, 0), angle);
    EXPECT_FALSE(intersection.doesIntersect());

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 4.2, 5), angle);
    assertMtv(intersection, Vector2D(0.02404, 0.01388));

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 4.3, 5), angle);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary1->intersects(boundary2.get(), Vector2D( 4.23, 4), angle);
    assertMtv(intersection, Vector2D(0.4346, 0.2509));

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 4.23, 6), angle);
    EXPECT_FALSE(intersection.doesIntersect());

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 3.9, 8.4), angle);
    EXPECT_FALSE(intersection.doesIntersect());
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

    UniqueBoundary boundary1 = BoundarySet::createBoundary(settings1);
    UniqueBoundary boundary2 = BoundarySet::createBoundary(settings2);

    SatIntersection intersection = boundary1->intersects(boundary2.get(), Vector2D( 0, 0),0);
    assertMtv(intersection, Vector2D(5.5, 0));

    intersection = boundary2->intersects(boundary1.get(), Vector2D( 0, 0),0);
    assertMtv(intersection, Vector2D(5.5, 0));


    intersection = boundary1->intersects(boundary2.get(), Vector2D( 2.4, 4.8),0);
    assertMtv(intersection, Vector2D(3.1, 0));

    intersection = boundary2->intersects(boundary1.get(), Vector2D(-2.4,-4.8),0);
    assertMtv(intersection, Vector2D(-3.1, 0));

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 2.6, 5.1),0);
    assertMtv(intersection, Vector2D(1.30147, 2.5529));

    intersection = boundary2->intersects(boundary1.get(), Vector2D(-2.6,-5.1),0);
    assertMtv(intersection, Vector2D(-1.30147, -2.5529));

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 2.4, 8.1),0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(-2.4,-8.1),0);
    EXPECT_FALSE(intersection.doesIntersect());

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 5.4, 0),0);
    assertMtv(intersection, Vector2D(0.1, 0));

    intersection = boundary2->intersects(boundary1.get(), Vector2D(-5.4, 0),0);
    assertMtv(intersection, Vector2D(-0.1, 0));

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 5.6, 0),0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(-5.6, 0),0);
    EXPECT_FALSE(intersection.doesIntersect());

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 0, 7.9),0);
    assertMtv(intersection, Vector2D(0, 0.1));

    intersection = boundary2->intersects(boundary1.get(), Vector2D( 0,-7.9),0);
    assertMtv(intersection, Vector2D(0, -0.1));

    intersection = boundary1->intersects(boundary2.get(), Vector2D(0, 8.1),0);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(0,-8.1),0);
    EXPECT_FALSE(intersection.doesIntersect());
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

    UniqueBoundary boundary1 = BoundarySet::createBoundary(settings1);
    UniqueBoundary boundary2 = BoundarySet::createBoundary(settings2);

    SatIntersection intersection = boundary1->intersects(boundary2.get(), Vector2D( 0, 0),angle);
    assertMtv(intersection, Vector2D(5.5, 0));

    intersection = boundary2->intersects(boundary1.get(), Vector2D( 0, 0),-angle);
    assertMtv(intersection, Vector2D( 4.763, -2.75));

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 5.4, 5),angle);
    assertMtv(intersection, Vector2D(0.1, 0));

    intersection = boundary1->intersects(boundary2.get(), Vector2D( 5.6, 5),angle);
    EXPECT_FALSE(intersection.doesIntersect());

    intersection = boundary2->intersects(boundary1.get(), Vector2D(4.77, 2.75), angle);
    EXPECT_FALSE(intersection.doesIntersect());
    intersection = boundary2->intersects(boundary1.get(), Vector2D(4.76, 2.75), angle);
    assertMtv(intersection, Vector2D( 0.0024, 0.0014));

    intersection = boundary2->intersects(boundary1.get(), Vector2D(4.76, 2.75), 0);
    assertMtv(intersection, Vector2D(0.74,0));
}

} // BattleRoom namespace

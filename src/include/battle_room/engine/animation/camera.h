#ifndef CAMERA_H
#define CAMERA_H

#include "battle_room/common/rel_pixel.h"
#include "battle_room/common/position.h"
#include "battle_room/common/resource_descriptor.h"


namespace BattleRoom {

class Camera {

public:

    Camera();

    Position& position();

    Position getPosition();
    void setPosition(Position pos);

    void rotateUpDown(radians theta);
    void rotateLeftRight(radians theta);
    void rotateClockwise(radians theta);

    RelPixel fromLocation(Vector3D location);
    Vector3D zeroPlaneIntersection(RelPixel pixel);

    void applySettings(ResourceDescriptor settings);

    radians getHorizontalFov();
    radians getVerticalFov();

private:

    Position m_position;

    Vector3D m_forward;
    Vector3D m_up;
    Vector3D m_right;

    radians m_horizontalFov = 1.308333; // 75 deg
    radians m_verticalFov = 1.308333; // based on window size

}; // Camera class
} // BattleRoom namespace
#endif // CAMERA_H

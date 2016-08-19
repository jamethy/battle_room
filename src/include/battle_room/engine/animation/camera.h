#ifndef CAMERA_H
#define CAMERA_H

#include "battle_room/common/position.h"
#include "battle_room/common/pixel.h"
#include "battle_room/common/resource_descriptor.h"


namespace BattleRoom {

class Camera {

public:

    Position& position();

    Position getPosition();
    void setPosition(Position pos);

    Pixel fromZeroPlane(Vector3D location);
    Vector3D zeroPlaneIntersection(Pixel pixel);

    void applySettings(ResourceDescriptor settings);

    px getHeight();
    px getWidth();
    radians getHorizontalFov();
    radians getVerticalFov();

private:

    Position m_position;

    radians m_horizontalFov = 1.308333; // 75 deg
    radians m_verticalFov = 1.308333; // based on window size
    px m_width;
    px m_height;

}; // Camera class
} // BattleRoom namespace
#endif // CAMERA_H

#ifndef CAMERA_H
#define CAMERA_H

#include "battle_room/common/position.h"
#include "battle_room/common/pixel.h"


namespace BattleRoom {

class Camera {

public:

    Position& position();

    Position getPosition();
    void setPosition(Position pos);

private:

    Position m_position;

}; // Camera class
} // BattleRoom namespace
#endif // CAMERA_H

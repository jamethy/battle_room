#ifndef CAMERA_H
#define CAMERA_H

#include "../utility/br_vectors.h"

namespace GraphicsInterface
{

typedef Utility::vec2d WorldPos;
typedef Utility::vec2i ScreenPos;

class CameraClass
{


public:

    CameraClass();
    ~CameraClass();

    int xFromWorld(WorldPos& pos);
    int yFromWorld(WorldPos& pos);
    ScreenPos posFromWorld(WorldPos& pos);
    int wFromWorld(double w);
    int hFromWorld(double h);


    double xFromScreen(ScreenPos& pos);
    double yFromScreen(ScreenPos& pos);
    WorldPos posFromScreen(ScreenPos& pos);
    double wFromScreen(double w);
    double hFromScreen(double h);

private:

    WorldPos& camPos();
    double& camTh();

    WorldPos m_camera_pos;
    double m_theta = 0;

};
}

#endif // CAMERA_H

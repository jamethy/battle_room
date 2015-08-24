#include "camera.h"

namespace GraphicsInterface
{


CameraClass::CameraClass()
{

}


CameraClass::~CameraClass()
{

}

int CameraClass::xFromWorld(GraphicsInterface::WorldPos &pos)
{
    return 0;
}

int CameraClass::yFromWorld(WorldPos &pos)
{
    return 0;
}

ScreenPos CameraClass::posFromWorld(WorldPos &pos)
{
    return ScreenPos();
}

int CameraClass::wFromWorld(double w)
{
    return 0;
}

int CameraClass::hFromWorld(double h)
{
    return 0;
}

double CameraClass::xFromScreen(ScreenPos &pos)
{
    return 0;
}

double CameraClass::yFromScreen(ScreenPos &pos)
{
    return 0;
}

WorldPos CameraClass::posFromScreen(ScreenPos &pos)
{
    return WorldPos();
}

double CameraClass::wFromScreen(double w)
{
    return 0;
}

double CameraClass::hFromScreen(double h)
{
    return 0;
}



WorldPos &CameraClass::camPos()
{
    return m_camera_pos;
}

double &CameraClass::camTh()
{
    return m_theta;
}

}

#ifndef CAMERA_H
#define CAMERA_H

#include "../utility/br_vectors.h"

namespace GraphicsInterface
{

using Utility::WorldPos;
using Utility::ScreenPos;

struct CameraPos
{
    CameraPos();
    CameraPos(const WorldPos& position, const double& Z, const double& theta);

    WorldPos pos;
    double z;
    double th;
};

class ZeroCalculator
{
public:
    ZeroCalculator(int width, int height, double fieldOfView);
    ~ZeroCalculator();

    void setWindowProperties(int width, int height, double fieldOfView);
    void setCameraPos(const CameraPos& pos);

    int xFromWorld(WorldPos& pos);
    int yFromWorld(WorldPos& pos);
    int wFromWorld(double w);
    int hFromWorld(double h);
    ScreenPos posFromWorld(WorldPos& pos);

    double xFromScreen(ScreenPos& pos);
    double yFromScreen(ScreenPos& pos);
    double wFromScreen(double w);
    double hFromScreen(double h);
    WorldPos posFromScreen(ScreenPos& pos);

private:

    int m_window_width;
    int m_window_height;

    double m_ppm_at_zero; // pixels per meter at zero
    WorldPos m_camera_pos;
    double m_camera_th;
    double m_fov;
};


class CameraClass
{

public:

    CameraClass(int width, int height, double fieldOfView = 1.3083);
    ~CameraClass();

    void setCameraBounds(const WorldPos &min, const WorldPos &max);
    void setWindowSize(int width, int height);

    void setCameraPosition(const CameraPos& pos);
    CameraPos getCameraPosition();

    void moveInX(const double& changeInX);
    void moveInY(const double& changeInY);
    void moveInZ(const double& changeInZ);
    void rotate(const double& changeInTh);

    void update();

    ZeroCalculator& getZeroCalculator();

private:

    void checkBounds();

    ZeroCalculator m_zerocalculator;

    WorldPos m_camera_pos;
    double m_camth = 0;
    double m_camz = 0;

    WorldPos m_minview;
    WorldPos m_maxview;

    double m_fov; // radians

};


bool operator==(const CameraPos& a, const CameraPos& b);

}

#endif // CAMERA_H

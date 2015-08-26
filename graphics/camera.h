#ifndef CAMERA_H
#define CAMERA_H

#include "../utility/br_vectors.h"

namespace GraphicsInterface
{

typedef Utility::vec2d WorldPos;
typedef Utility::vec2i ScreenPos;

class ZeroCalculator
{
public:
    ZeroCalculator(int width, int height, double fieldOfView);
    ~ZeroCalculator();

    void setWindowProperties(int width, int height, double fieldOfView);
    void setCameraPos(const WorldPos& pos, const double& theta, const double& z);

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

    void setCameraBounds(WorldPos& min, WorldPos& max);
    void setWindowSize(int width, int height);

    void moveInX(double changeInX);
    void moveInY(double changeInY);
    void moveInZ(double changeInZ);

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
}

#endif // CAMERA_H

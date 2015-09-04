#ifndef CAMERA_H
#define CAMERA_H

#include "interfaces/graphics_interface.h"
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
    double _z;
    double th;

    double& x();
    double& y();
    double& z();
};

class ZeroCalculator
{
public:
    ZeroCalculator(int width, int height, double fieldOfView);
    ~ZeroCalculator();

    void setWindowProperties(int width, int height, double fieldOfView);
    int getWindowWidth();
    int getWindowHeight();
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
    CameraPos m_camera_pos;
    double m_fov;
};


class CameraClass : public CameraObjectClas
{

public:

    CameraClass(int width, int height, double fieldOfView = 1.3083);
    ~CameraClass();

    void setCameraBounds(const WorldPos& minPoint, const WorldPos& maxPoint);
    void setWindowSize(int width, int height);

    void setCameraPosition(const CameraPos& pos);
    CameraPos getCameraPosition();

    void update();

    ZeroCalculator& getZeroCalculator();

    // inherited
    void setPos(const Utility::vec2d& pos);
    void setTh(const double& theta);
    void setZ(const double& z);

    Utility::vec2d& getPos();
    double& getTh();
    double& getZ();

private:

    void checkBounds();
    void calculateBounds();

    ZeroCalculator m_zerocalculator;

    int m_window_width;
    int m_window_height;

    double m_minz;
    double m_maxz;
    double m_maxview_w;
    double m_maxview_h;
    double m_minview_w;
    double m_minview_h;

    CameraPos m_camera_pos;

    WorldPos m_minbound;
    WorldPos m_maxbound;

    double m_fov; // radians
    double m_fov_vert;

};


bool operator==(const CameraPos& a, const CameraPos& b);

}

#endif // CAMERA_H

#include "camera.h"
#include <cmath>

namespace GraphicsInterface
{


CameraClass::CameraClass(int width, int height, double fieldOfView) :
    m_zerocalculator(width, height, fieldOfView),
    m_camera_pos(WorldPos(0,0)),
    m_camth(0),
    m_camz(7.5),
    m_fov(fieldOfView)
{
    getZeroCalculator().setCameraPos(m_camera_pos,m_camth,m_camz);
}


CameraClass::~CameraClass()
{

}

void CameraClass::setCameraBounds(WorldPos& min, WorldPos& max)
{
    m_minview = min;
    m_maxview = max;
}

void CameraClass::setWindowSize(int width, int height)
{
    getZeroCalculator().setWindowProperties(width,height,m_fov);
}



void CameraClass::moveInX(double changeInX)
{
    m_camera_pos.x() += changeInX;
    checkBounds();
}

void CameraClass::moveInY(double changeInY)
{
    m_camera_pos.y() += changeInY;
    checkBounds();
}

void CameraClass::moveInZ(double changeInZ)
{
    m_camz += changeInZ;
    checkBounds();
}

void CameraClass::update()
{
    getZeroCalculator().setCameraPos(m_camera_pos,m_camth,m_camz);
}

ZeroCalculator &CameraClass::getZeroCalculator()
{
    return m_zerocalculator;
}

void CameraClass::checkBounds()
{

}

//////////// Zero Calculator /////////////////////////////////////////////////////////////////


ZeroCalculator::ZeroCalculator(int width, int height, double fieldOfView)
    : m_window_width(width),
      m_window_height(height),
      m_fov(fieldOfView)
{

}


ZeroCalculator::~ZeroCalculator()
{

}

void ZeroCalculator::setWindowProperties(int width, int height, double fieldOfView)
{
   m_window_width = width;
   m_window_height = height;
   m_fov = fieldOfView;
}

void ZeroCalculator::setCameraPos(const WorldPos &pos, const double &theta, const double &z)
{
    m_camera_pos = pos;
    m_camera_th = theta;

    double width_of_view = 2.0*z*std::tan(m_fov/2.0); // in meters
    m_ppm_at_zero = m_window_width/width_of_view;
}



int ZeroCalculator::xFromWorld(GraphicsInterface::WorldPos &pos)
{
    double dx = (pos.x()- m_camera_pos.x())*cos(-m_camera_th) - (pos.y()-m_camera_pos.y())*sin(-m_camera_th);
    return dx*m_ppm_at_zero + m_window_width/2.0;
}

int ZeroCalculator::yFromWorld(WorldPos &pos)
{
    double dy = (pos.x()- m_camera_pos.x())*sin(-m_camera_th) + (pos.y()-m_camera_pos.y())*cos(-m_camera_th);
    return dy*m_ppm_at_zero + m_window_height/2.0;
}

ScreenPos ZeroCalculator::posFromWorld(WorldPos &pos)
{
    Utility::vec2d v = pos-m_camera_pos;
    v.rotate(-m_camera_th);
    v.x() = m_ppm_at_zero*v.x() + m_window_width/2.0;
    v.y() = m_ppm_at_zero*v.y() + m_window_height/2.0;
    return ScreenPos(v.x(),v.y());
}

int ZeroCalculator::wFromWorld(double w)
{
    return w*m_ppm_at_zero;
}

int ZeroCalculator::hFromWorld(double h)
{
    return h*m_ppm_at_zero;
}

double ZeroCalculator::xFromScreen(ScreenPos &pos)
{
    double dx = (pos.x() - m_window_width/2.0)/m_ppm_at_zero;
    double dy = (pos.y() - m_window_height/2.0)/m_ppm_at_zero;
    return dx*cos(m_camera_th) - dy*sin(m_camera_th) + m_camera_pos.x();
}

double ZeroCalculator::yFromScreen(ScreenPos &pos)
{
    double dx = (pos.x() - m_window_width/2.0)/m_ppm_at_zero;
    double dy = (pos.y() - m_window_height/2.0)/m_ppm_at_zero;
    return dx*sin(m_camera_th) + dy*cos(m_camera_th) + m_camera_pos.y();
}

WorldPos ZeroCalculator::posFromScreen(ScreenPos &pos)
{
    WorldPos retvec;
    double dx = (pos.x() - m_window_width/2.0)/m_ppm_at_zero;
    double dy = (pos.y() - m_window_height/2.0)/m_ppm_at_zero;
    retvec.x() = dx*cos(m_camera_th) - dy*sin(m_camera_th) + m_camera_pos.x();
    retvec.y() = dx*sin(m_camera_th) + dy*cos(m_camera_th) + m_camera_pos.y();
    return retvec;
}

double ZeroCalculator::wFromScreen(double w)
{
    return w/m_ppm_at_zero;
}

double ZeroCalculator::hFromScreen(double h)
{
    return h/m_ppm_at_zero;
}

} // end

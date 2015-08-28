#include "camera.h"
#include <cmath>

namespace GraphicsInterface
{

using Utility::WorldPos;
using Utility::ScreenPos;

CameraClass::CameraClass(int width, int height, double fieldOfView) :
    m_zerocalculator(width, height, fieldOfView),
    m_camera_pos(WorldPos(0,0)),
    m_camth(0),
    m_camz(7.5),
    m_fov(fieldOfView),
    m_window_width(width),
    m_window_height(height)
{
    m_fov_h = 2*atan(height*tan(m_fov/2.0)/width);
    getZeroCalculator().setCameraPos(getCameraPosition());
}


CameraClass::~CameraClass()
{

}

void CameraClass::setCameraBounds(const Utility::WorldPos &minPoint, const Utility::WorldPos &maxPoint)
{
    m_minbound = minPoint;
    m_maxbound = maxPoint;
    calculateBounds();
}

void CameraClass::setWindowSize(int width, int height)
{
    getZeroCalculator().setWindowProperties(width,height,m_fov);
}

void CameraClass::setCameraPosition(const CameraPos &pos)
{
    m_camera_pos = pos.pos;
    m_camz = pos.z;
    m_camth = pos.th;
}

CameraPos CameraClass::getCameraPosition()
{
    return CameraPos(m_camera_pos,m_camz,m_camth);
}



void CameraClass::moveInX(const double& changeInX)
{
    m_camera_pos.x() += changeInX;
}

void CameraClass::moveInY(const double& changeInY)
{
    m_camera_pos.y() += changeInY;
}

void CameraClass::moveInZ(const double& changeInZ)
{
    m_camz += changeInZ;
}

void CameraClass::rotate(const double& changeInTh)
{
    m_camth += changeInTh;
    calculateBounds();
}

void CameraClass::update()
{
    checkBounds();
    getZeroCalculator().setCameraPos(getCameraPosition());
}

ZeroCalculator &CameraClass::getZeroCalculator()
{
    return m_zerocalculator;
}


void CameraClass::checkBounds()
{

    double camx = m_camera_pos.x();
    double camy = m_camera_pos.y();

    double minx = -m_camz*tan(m_fov/2)   + camx*cos(-m_camth) - camy*sin(-m_camth);
    double miny = -m_camz*tan(m_fov_h/2) + camx*sin(-m_camth) + camy*cos(-m_camth);
    double maxx =  m_camz*tan(m_fov/2)   + camx*cos(-m_camth) - camy*sin(-m_camth);
    double maxy =  m_camz*tan(m_fov_h/2) + camx*sin(-m_camth) + camy*cos(-m_camth);

    if (camx < m_minbound.x())
        camx = m_minbound.x();
    else if (camx > m_maxbound.x())
        camx = m_maxbound.x();
    else if (maxx > m_maxview_w){
        camx -=  (maxx-m_maxview_w)*cos(-m_camth);
        camy -= -(maxx-m_maxview_w)*sin(-m_camth);
    }
    else if (minx < m_minview_w){
        camx -=  (minx-m_minview_w)*cos(-m_camth);
        camy -= -(minx-m_minview_w)*sin(-m_camth);
    }

    if (camy < m_minbound.y())
        camy = m_minbound.y();
    else if (camy > m_maxbound.y())
        camy = m_maxbound.y();
    else if (maxy > m_maxview_h){
        camx -= (maxy-m_maxview_h)*sin(-m_camth);
        camy -= (maxy-m_maxview_h)*cos(-m_camth);
    }
    else if (miny < m_minview_h){
        camx -= (miny-m_minview_h)*sin(-m_camth);
        camy -= (miny-m_minview_h)*cos(-m_camth);
    }

    m_camera_pos = WorldPos(camx,camy);
}

void CameraClass::calculateBounds()
{

    // find horizontal
    m_minview_w = m_minbound.x()*cos(-m_camth) - m_minbound.y()*sin(-m_camth);
    m_maxview_w = m_minview_w;

    double p = m_minbound.x()*cos(-m_camth) - m_maxbound.y()*sin(-m_camth);
    if (p < m_minview_w) m_minview_w = p;
    else if (p > m_maxview_w) m_maxview_w = p;

    p = m_maxbound.x()*cos(-m_camth) - m_maxbound.y()*sin(-m_camth);
    if (p < m_minview_w) m_minview_w = p;
    else if (p > m_maxview_w) m_maxview_w = p;

    p = m_maxbound.x()*cos(-m_camth) - m_minbound.y()*sin(-m_camth);
    if (p < m_minview_w) m_minview_w = p;
    else if (p > m_maxview_w) m_maxview_w = p;

    // find vertical
    m_minview_h = m_minbound.x()*sin(-m_camth) + m_minbound.y()*cos(-m_camth);
    m_maxview_h = m_minview_h;

    p = m_minbound.x()*sin(-m_camth) + m_maxbound.y()*cos(-m_camth);
    if (p < m_minview_h) m_minview_h = p;
    else if (p > m_maxview_h) m_maxview_h = p;

    p = m_maxbound.x()*sin(-m_camth) + m_maxbound.y()*cos(-m_camth);
    if (p < m_minview_h) m_minview_h = p;
    else if (p > m_maxview_h) m_maxview_h = p;

    p = m_maxbound.x()*sin(-m_camth) + m_minbound.y()*cos(-m_camth);
    if (p < m_minview_h) m_minview_h = p;
    else if (p > m_maxview_h) m_maxview_h = p;

    // change to be ratio of screen
    double w = m_maxview_w - m_minview_w;
    double h = m_maxview_h - m_minview_h;
    double R = m_window_width/(1.0*m_window_height);
    if (R*h > w){
        double midx = (m_maxview_w + m_minview_w)/2;
        m_minview_w = midx - R*h/2;
        m_maxview_w = midx + R*h/2;
    }
    else{
        double midy = (m_maxview_h + m_minview_h)/2;
        m_minview_h = midy - w/R/2;
        m_maxview_h = midy + w/R/2;
    }

    double zw = (m_maxview_w - m_minview_w)/2/tan(m_fov/2);
    double zh = (m_maxview_h - m_minview_h)/2/tan(m_fov_h/2);

    m_maxz = (zw > zh) ? zw : zh;
    m_minz = 1.5;
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

void ZeroCalculator::setCameraPos(const CameraPos &pos)
{
    m_camera_pos = pos.pos;
    m_camera_th = pos.th;

    double width_of_view = 2.0*pos.z*std::tan(m_fov/2.0); // in meters
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


CameraPos::CameraPos(){}
CameraPos::CameraPos(const WorldPos& position, const double& Z, const double& theta)
    :pos(position), z(Z), th(theta) {}
bool operator==(const CameraPos& a, const CameraPos& b)
{
    return (a.pos == b.pos) && (a.z == b.z) && (a.th == b.th);
}

} // end

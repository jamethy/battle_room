#include "br_vectors.h"

#include <cmath>
#include <algorithm>

namespace Utility{

vec2d::vec2d(){}
vec2d::vec2d(double x, double y) : m_x(x),m_y(y){}

double& vec2d::x(){return m_x;}
double& vec2d::y(){return m_y;}
double  vec2d::r(){return sqrt(m_x*m_x + m_y*m_y);}
double vec2d::r2(){return m_x*m_x + m_y*m_y;}


bool vec2d::is_in(std::vector<vec2d>& points)
{
    return ( std::find(points.begin(),points.end(), *this) == points.end() );
}

void vec2d::normalize()
{
    double radius = r();
    m_x /= radius;
    m_y /= radius;
}

void vec2d::rotate(double theta)
{
    double tempx = m_x;
    m_x = m_x*cos(theta) - m_y*sin(theta);
    m_y = tempx*sin(theta) + m_y*cos(theta);
}

void vec2d::rotate_about(double theta, const vec2d& origin)
{
    vec2d relative_point  = *this - origin;
    relative_point.rotate(theta);
    *this = origin + relative_point;
}

double dot(const vec2d& a, const vec2d& b){ return a.m_x*b.m_x + a.m_y*b.m_y; }
bool operator==(const vec2d& a, const vec2d& b){ return a.m_x==b.m_x && a.m_y==b.m_y; }
vec2d operator-(const vec2d& a, const vec2d& b){ return vec2d(a.m_x-b.m_x,a.m_y-b.m_y); }
vec2d operator+(const vec2d& a, const vec2d& b){ return vec2d(a.m_x+b.m_x,a.m_y+b.m_y); }
vec2d operator*(const vec2d& a, const vec2d& b){ return vec2d(a.m_x*b.m_x,a.m_y*b.m_y); }
vec2d operator/(const vec2d& a, const vec2d& b){ return vec2d(a.m_x/b.m_x,a.m_y/b.m_y); }

vec2d operator*(const vec2d& a, double mag){return vec2d(a.m_x*mag,a.m_y*mag);}
vec2d operator*(double mag, const vec2d& a){return vec2d(a.m_x*mag,a.m_y*mag);}
vec2d operator/(const vec2d& a, double mag){return vec2d(a.m_x/mag,a.m_y/mag);}
vec2d operator/(double mag, const vec2d& a){return vec2d(mag/a.m_x,mag/a.m_y);}
vec2d operator+(const vec2d& a, double mag){return vec2d(a.m_x+mag,a.m_y+mag);}
vec2d operator-(const vec2d& a, double mag){return vec2d(a.m_x-mag,a.m_y-mag);}

void vec2d::operator+=(const vec2d& b){ m_x+=b.m_x; m_y+=b.m_y; }
void vec2d::operator-=(const vec2d& b){ m_x-=b.m_x; m_y-=b.m_y; }
void vec2d::operator+=(double mag){m_x+=mag; m_y+=mag;}
void vec2d::operator-=(double mag){m_x-=mag; m_y-=mag;}

void vec2d::operator=(double mag){ m_x=mag; m_y=mag; }
vec2d vec2d::operator-(){ return vec2d(-m_x, -m_y); }
double &vec2d::operator[](const unsigned int& n){ return (n==0 ? m_x : m_y); }

std::ostream& operator<<(std::ostream& os, const vec2d& a){
    os << a.m_x << " " << a.m_y;
    return os;
}
std::istream& operator>>(std::istream& is, vec2d& a){
    is >> a.m_x >> a.m_y;
    return is;
}



vec2i::vec2i(){}
vec2i::vec2i(int x, int y) : m_x(x),m_y(y){}

int& vec2i::x(){return m_x;}
int& vec2i::y(){return m_y;}

} // Utility namespace

#ifndef VECTORS_H
#define VECTORS_H

#include <iostream>
#include <vector>

namespace Utility{


/*!
 * \brief The vec2d class is a two dimension vector mainly used for bounding points in the game.
 */
class vec2d {

public:

    // Get Value Functions
    double& x(); //!< Return x value, or first element
    double& y(); //!< Return y value, or second element
    double  r(); //!< Calculates and returns length of vector
    double r2(); //!< Calculates and returns square of length


    void normalize();

    void rotate(double theta);

    void rotate_about(double theta, const vec2d& origin);

    bool is_in(std::vector<vec2d>& points);

    friend double dot(const vec2d& a, const vec2d& b);
    friend bool operator==(const vec2d& a, const vec2d& b);
    friend vec2d operator-(const vec2d& a, const vec2d& b);
    friend vec2d operator+(const vec2d& a, const vec2d& b);
    friend vec2d operator*(const vec2d& a, const vec2d& b);
    friend vec2d operator/(const vec2d& a, const vec2d& b);

    friend vec2d operator*(const vec2d& a, double mag);
    friend vec2d operator*(double mag, const vec2d& a);
    friend vec2d operator/(const vec2d& a, double mag);
    friend vec2d operator/(double mag, const vec2d& a);
    friend vec2d operator+(const vec2d& a, double mag);
    friend vec2d operator-(const vec2d& a, double mag);

    void operator+=(const vec2d& b);
    void operator-=(const vec2d& b);
    void operator+=(double mag);
    void operator-=(double mag);

    void operator=(double mag);

    vec2d operator-();
    double &operator[](const unsigned int& n);


    friend std::ostream& operator<<(std::ostream& os, const vec2d& a);
    friend std::istream& operator>>(std::istream& is, vec2d& a);


    // constructors
    vec2d();
    vec2d(double x, double y);


private:

    double m_x = 0; ///< First position in the vector
    double m_y = 0; ///< Second position in the vector
};


} // deathblade namespace

#endif // VECTORS_H

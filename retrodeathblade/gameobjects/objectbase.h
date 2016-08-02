#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "controller_base/gameenums.h"
#include "controller_camera/cameracontrol.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"

#include <vector>

/*!
 * \brief The vec2d class is a two dimension vector mainly used for bounding points in the game.
 */
class vec2d {

public:
    vec2d(){x=0;y=0;}
    vec2d(double x, double y){
        this->x = x;
        this->y = y;
    }
    double x,y;

    double dot(const vec2d other){ return x*other.x + y*other.y; }
    vec2d operator+(const vec2d other){ return vec2d(x+other.x,y+other.y); }
    vec2d operator-(const vec2d other){ return vec2d(x-other.x,y-other.y); }
    vec2d operator*(const double mag){ return vec2d(x*mag, y*mag); }
    double &operator[](unsigned int n){ return (n==0 ? x : y); }
};


/*!
 * \brief The ObjectBaseClass class is the highest level of object. It mainly contains
 * positioning information and virtual functions needed by all children.
 */
class ObjectBaseClass {

public:
    ObjectBaseClass();
    virtual ~ObjectBaseClass();


    double x,y,th; //!< Position and angle of object
    double dx,dy,dth; //!< Speed of object
    double mass, elasticity, friction; //!< Characteristics of object related to collision.
    db::ZPlane zplane; //!< Depth of object used for drawing
    std::vector<vec2d> side_normals; //!< Normal vectors of the bounding line segments, used in collision.
    std::vector<vec2d> bounding_points; //!< Points bounding the object, used in collision.

    /*!
     * \brief Moves the object, namely shifts values x,y and bounding points.
     * \param delx Change in x to move.
     * \param dely Change in y to move.
     */
    void translate(double delx, double dely);

    /*!
     * \brief Rotates the object, namely shifts th.
     * \param deltheta Change in theta to rotate (positive is clockwise).
     */
    void rotate(double deltheta);

    /*!
     * \brief Sorts the points and calls calculate_normals().
     * \bug square_r method does not work well. Should replace with quad tree?
     */
    void organize_points();

    /*!
     * \brief Uses bounding_points to calculate normal vectors to the edges of the object.
     */
    void calculate_normals();

    /*!
     * \brief Projects the object onto an axis, used in collision.
     * \param axis Axis to be projected onto.
     * \return Two dimensional vector with [0]/x being the minimum on axis and [1]/y the maximum.
     */
    vec2d project_onto(vec2d &axis);

    double square_r; //!< Maximum radius squared. Not working...

    // Inherited members.
    virtual void step_time();
    virtual void drawon(SDL_Renderer* renderer, CameraControl* camera);
    virtual bool isMobile(){return false;}
    virtual bool isPlayer(){return false;}

private:

    /*!
     * \brief The clockwise struct is used to sort the bounding_points in a clockwise order. See organize_points();
     */
    struct clockwise {
        clockwise(const ObjectBaseClass& c) : theshape(c) {}
        bool operator () (const vec2d& a, const vec2d& b){
            double atheta = atan2(a.y-theshape.y,a.x-theshape.x);
            double btheta = atan2(b.y-theshape.y,b.x-theshape.x);
            return atheta < btheta;
        }
        const ObjectBaseClass& theshape;
    };
};


#endif // OBJECTBASE_H

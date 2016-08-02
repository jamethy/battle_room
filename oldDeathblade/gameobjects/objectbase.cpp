#include "objectbase.h"

#include <algorithm>

ObjectBaseClass::ObjectBaseClass(){

    x = 0; y = 0; th = 0; zplane = db::Player;
    dx = 0; dy = 0; dth = 0;
    mass = 0; elasticity = 1; friction = 1;
    square_r = 0;
}

ObjectBaseClass::~ObjectBaseClass(){

}

void ObjectBaseClass::step_time(){
}


void ObjectBaseClass::drawon(SDL_Renderer *renderer, CameraControl *camera){
    (void)renderer;
    (void)camera;
}

// dealing with points

void ObjectBaseClass::organize_points(){
    std::sort(bounding_points.begin(),bounding_points.end(),clockwise(*this));
    calculate_normals();

    square_r = 0;
    for(unsigned int i = 0; i < bounding_points.size(); ++i){
        vec2d relpoint(bounding_points[i].x-x,bounding_points[i].y-y);
        double r2 = relpoint.x*relpoint.x + relpoint.y + relpoint.y;
        if(r2 > square_r) square_r = r2;
    }
    square_r += 3;
}

void ObjectBaseClass::calculate_normals(){
    for(unsigned int i = 0; i < bounding_points.size(); ++i){
        vec2d normal;
        normal.x = bounding_points[i].x - bounding_points[(i+1==bounding_points.size()) ? 0 : i+1].x;
        normal.y = bounding_points[i].y - bounding_points[(i+1==bounding_points.size()) ? 0 : i+1].y;

        double r = sqrt(normal.x*normal.x+normal.y*normal.y);
        normal.x /= r;
        normal.y /= r;

        bool unique = true;
        for(unsigned int j = 0; j < side_normals.size(); ++j){
            if(normal.x == side_normals[j].x && normal.y == side_normals[j].y){
                unique = false;
                break;
            }
            if(normal.x == -side_normals[j].x && normal.y == -side_normals[j].y){
                unique = false;
                break;
            }
        }

        if(unique) side_normals.push_back(normal);
    }
}

vec2d ObjectBaseClass::project_onto(vec2d& axis)
{
    vec2d minmax(-10e10,-10e10);

    if(bounding_points.size() == 0){
        return minmax;
    }
    minmax[0] = axis.dot(bounding_points[0]);
    minmax[1] = minmax[0];

    std::vector<vec2d>::iterator bp;
    for(bp = bounding_points.begin(); bp != bounding_points.end(); ++bp){
        double p = axis.dot((*bp));
        if(p < minmax[0]) minmax[0] = p;
        else if(p > minmax[1]) minmax[1] = p;
    }

    return minmax;
}

void ObjectBaseClass::translate(double delx, double dely){

    if(delx == 0 && dely == 0) return;

    x += delx;
    y += dely;

    std::vector<vec2d>::iterator bp;
    for(bp = bounding_points.begin(); bp != bounding_points.end(); ++bp){
        (*bp).x += delx;
        (*bp).y += dely;
    }
}

void ObjectBaseClass::rotate(double deltheta){

    if(deltheta == 0) return;

    th += deltheta;

    double cos_deltheta = cos(deltheta);
    double sin_deltheta = sin(deltheta);

    std::vector<vec2d>::iterator bp;
    for(bp = bounding_points.begin(); bp != bounding_points.end(); ++bp){
        vec2d relpoint;
        relpoint.x = (*bp).x - x;
        relpoint.y = (*bp).y - y;

        (*bp).x = x + (relpoint.x*cos_deltheta - relpoint.y*sin_deltheta);
        (*bp).y = y + (relpoint.x*sin_deltheta + relpoint.y*cos_deltheta);
    }

    for(bp = side_normals.begin(); bp != side_normals.end(); ++bp){
        vec2d old = (*bp);

        (*bp).x = old.x*cos_deltheta - old.y*sin_deltheta;
        (*bp).y = old.x*sin_deltheta + old.y*cos_deltheta;
    }
}



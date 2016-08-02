#include "gameobjects/basicwall.h"

BasicWall::BasicWall()
{
    color.r = 100;
    color.g = 100;
    color.b = 100;
    color.a = 255;
}
BasicWall::~BasicWall()
{
}

void BasicWall::create(double x, double y, double w, double h){
    this->x = x + w/2; this->y = y + h/2;

    bounding_points.clear();
    bounding_points.push_back(vec2d(x,   y  ));
    bounding_points.push_back(vec2d(x+w, y  ));
    bounding_points.push_back(vec2d(x+w, y+h));
    bounding_points.push_back(vec2d(x,   y+h));

    organize_points();
}

void BasicWall::drawon(SDL_Renderer *renderer, CameraControl* camera){

    std::vector<Sint16> vx; vx.resize(bounding_points.size());
    std::vector<Sint16> vy; vy.resize(bounding_points.size());
    for(unsigned int i = 0; i < bounding_points.size(); ++i){
        vx[i] = camera->pixelfromx(bounding_points[i].x, bounding_points[i].y, db::Player);
        vy[i] = camera->pixelfromy(bounding_points[i].x, bounding_points[i].y, db::Player);
    }
    filledPolygonRGBA(renderer,vx.data(),vy.data(),bounding_points.size(),color.r,color.g,color.b,color.a);
}

void BasicWall::set_color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha){
    color.r = red;
    color.g = green;
    color.b = blue;
    color.a = alpha;
}

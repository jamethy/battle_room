#include "gameobjects/star.h"

Star::Star(){
    star_texture = NULL;
    texturewidth = 0;
    textureheight = 0;
    mass = 10000;
}

Star::~Star(){

}

void Star::setTexture(SDL_Texture* star_texture, double width, double height){
    this->star_texture = star_texture;
    texturewidth = width;
    textureheight = height;

    bounding_points.clear();
    bounding_points.push_back(vec2d(x-width/2.0,y-height/2.0));
    bounding_points.push_back(vec2d(x+width/2.0,y-height/2.0));
    bounding_points.push_back(vec2d(x+width/2.0,y+height/2.0));
    bounding_points.push_back(vec2d(x-width/2.0,y+height/2.0));

    organize_points();
}

void Star::step_time()
{
    translate(dx,dy);
    rotate(dth);
}


void Star::drawon(SDL_Renderer *renderer, CameraControl *camera){

    if(star_texture == NULL) return;


    SDL_Rect dst = camera->calculate_display_destination(
                x,
                y,
                texturewidth,
                textureheight,
                zplane);

    SDL_RenderCopyEx(renderer, star_texture, NULL, &dst, (th-camera->camyaw)*180.0/3.14159265359, NULL, SDL_FLIP_NONE);

}

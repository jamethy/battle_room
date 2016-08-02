#include "player.h"

Player::Player(){
    character_texture = NULL;
    texturewidth = 0;
    textureheight = 0;
    mass = 150;
}

Player::~Player(){

}

void Player::rebound()
{
    if(bound.enabled){
        dx = bound.xdrag*0.0001;
        dy = bound.ydrag*0.0001;
        bound.enabled = false;

        if(dx > 0.05) dx = 0.05;
        else if(dx < -0.05) dx = -0.05;
        if(dy > 0.05) dy = 0.05;
        else if(dy < -0.05) dy = -0.05;
    }
}

void Player::step_time(){
    translate(dx,dy);
    rotate(dth);
}

void Player::setTexture(SDL_Texture* player_texture, double width, double height){
    character_texture = player_texture;
    texturewidth = width;
    textureheight = height;

    bounding_points.clear();
    bounding_points.push_back(vec2d(x-width/2.0,y-height/2.0));
    bounding_points.push_back(vec2d(x+width/2.0,y-height/2.0));
    bounding_points.push_back(vec2d(x+width/2.0,y+height/2.0));
    bounding_points.push_back(vec2d(x-width/2.0,y+height/2.0));

    organize_points();

}

void Player::drawon(SDL_Renderer *renderer, CameraControl *camera){

    if(character_texture == NULL) return;

    SDL_Rect dst = camera->calculate_display_destination(
                x,
                y,
                texturewidth,
                textureheight,
                zplane);

    SDL_RenderCopyEx(renderer, character_texture, NULL, &dst, (th-camera->camyaw)*180.0/3.14159265359, NULL, SDL_FLIP_NONE);

}

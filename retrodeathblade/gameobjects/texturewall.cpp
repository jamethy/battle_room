#include "gameobjects/texturewall.h"

TextureWall::TextureWall()
{
    wall_texture = NULL;
    width = 0;
    height = 0;
    mass = -1; //not mobile
}
TextureWall::~TextureWall()
{
}

void TextureWall::setTexture(SDL_Texture* wall_texture, double width, double height){
    this->wall_texture = wall_texture;
    this->width = width;
    this->height = height;

    bounding_points.clear();
    bounding_points.push_back(vec2d(x-width/2.0,y-height/2.0));
    bounding_points.push_back(vec2d(x+width/2.0,y-height/2.0));
    bounding_points.push_back(vec2d(x+width/2.0,y+height/2.0));
    bounding_points.push_back(vec2d(x-width/2.0,y+height/2.0));

    organize_points();
}

void TextureWall::drawon(SDL_Renderer *renderer, CameraControl* camera){

    if(wall_texture == NULL) return;

    SDL_Rect dst = camera->calculate_display_destination(
                x,
                y,
                width,
                height,
                zplane);

    SDL_RenderCopyEx(renderer, wall_texture, NULL, &dst, (-camera->camyaw)*180.0/3.14159265359, NULL, SDL_FLIP_NONE);
}

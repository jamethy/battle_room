#include "boundclass.h"

BoundClass::BoundClass()
{
    xclick = 0;
    yclick = 0;
    xdrag = 0;
    ydrag = 0;
    enabled = false;
}

BoundClass::~BoundClass()
{
}

//void BoundClass::attach_object()

void BoundClass::drawon(SDL_Renderer *renderer, CameraControl *camera)
{
    if( !enabled ) return;

    int xpoint = camera->pixelfromx(xclick,yclick,db::Player);
    int ypoint = camera->pixelfromy(xclick,yclick,db::Player);

    SDL_Rect clickpoint = {xpoint-25,ypoint-25,50,50};
    SDL_SetRenderDrawColor(renderer,200,50,50,100);
    SDL_RenderDrawRect(renderer,&clickpoint);

    SDL_RenderDrawLine(renderer, xpoint, ypoint, xpoint+xdrag, ypoint+ydrag);


}

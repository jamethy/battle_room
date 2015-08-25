#include "animation_star.h"
#include <iostream>
namespace GraphicsInterface
{


StarAnimation::StarAnimation(double duration) : SDLAnimationClass(duration)
{
}

StarAnimation::~StarAnimation(){}

UniqueTexture StarAnimation::StarTexture = UniqueTexture(nullptr);


SDL_Texture* StarAnimation::getTexture(SDL_Renderer* renderer)
{
    if(StarAnimation::StarTexture == nullptr)
    {
        std::string filename = getResourcePath() + "star.png";
        StarAnimation::StarTexture = UniqueTexture(IMG_LoadTexture(renderer,filename.c_str()),SDL_Deleter());
        if(StarAnimation::StarTexture.get() == nullptr)
        {
            std::cerr << "Failed to load star texture.\n";
        }
    }
    return StarAnimation::StarTexture.get();
}


class StarNoAnimation : public StarAnimation
{
public:
    StarNoAnimation() : StarAnimation(0) {}
    ~StarNoAnimation(){}
    void update(double time){}
    bool isComplete(){ return false; }
    AnimationType after(){ return NoAnimation; }

    void renderOn(SDL_Renderer* renderer, CameraClass& cam)
    {
        ScreenPos sp = cam.posFromWorld(getPosition());

        SDL_Rect dst_rect;
        dst_rect.x = sp.x();
        dst_rect.y = sp.y();
        dst_rect.w = cam.wFromWorld(1);
        dst_rect.h = cam.hFromWorld(1);


        SDL_Point center;
        center.x = cam.wFromWorld(0.5);
        center.y = cam.hFromWorld(0.5);

        SDL_RenderCopyEx(renderer,
                        getTexture(renderer),
                        src_rect,
                        &dst_rect,
                        getTheta(),
                        &center, SDL_FLIP_NONE);

    }
    SDL_Rect* src_rect = nullptr;
};




UniqueAnimation createStarAnimation(AnimationType animation)
{
    switch (animation) {
    case NoAnimation:
        return UniqueAnimation(new StarNoAnimation());
    default:
        return UniqueAnimation(new StarNoAnimation());
    }
}


} // end GraphicsInterface

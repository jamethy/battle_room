#include "animation_star.h"
#include <iostream>
namespace GraphicsInterface
{


StarAnimation::StarAnimation(double duration) : SDLAnimationClass(duration)
{
}

StarAnimation::~StarAnimation(){}

TextureMap StarAnimation::textureMap = TextureMap();

SDL_Texture* StarAnimation::getTexture(SDL_Renderer* renderer)
{
    UniqueTexture& texture = StarAnimation::textureMap[renderer];
    if(texture.get() == nullptr)
    {
        texture = loadUniqueTexture(renderer, "star.png");

        if(texture.get() == nullptr)
        {
            std::cerr << "Failed to load star texture.\n";
        }
    }
    return texture.get();
}


class StarNoAnimation : public StarAnimation
{
public:
    StarNoAnimation() : StarAnimation(0) {}
    ~StarNoAnimation(){}
    void update(double time){}
    bool isComplete(){ return false; }
    AnimationType after(){ return NoAnimation; }

    void renderOn(SDL_Renderer* renderer, ZeroCalculator& camcalc)
    {
        ScreenPos sp = camcalc.posFromWorld(getPosition());

        SDL_Rect dst_rect;
        dst_rect.x = sp.x();
        dst_rect.y = sp.y();
        dst_rect.w = camcalc.wFromWorld(2);
        dst_rect.h = camcalc.hFromWorld(2);

        SDL_RenderCopyEx(renderer,
                        getTexture(renderer),
                        src_rect,
                        &dst_rect,
                        getTheta(),
                        nullptr, SDL_FLIP_NONE);

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

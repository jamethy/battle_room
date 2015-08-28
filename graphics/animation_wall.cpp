#include "animation_wall.h"
#include <iostream>

namespace GraphicsInterface
{

WallAnimation::WallAnimation(double duration) : SDLAnimationClass(duration){}
WallAnimation::~WallAnimation(){}

TextureMap WallAnimation::textureMap = TextureMap();


SDL_Texture* WallAnimation::getTexture(SDL_Renderer* renderer)
{
    UniqueTexture& texture = WallAnimation::textureMap[renderer];
    if(texture.get() == nullptr)
    {
        texture = loadUniqueTexture(renderer, "wall.png");

        if(texture.get() == nullptr)
        {
            std::cerr << "Failed to load player texture.\n";
        }
    }
    return texture.get();
}


class WallNoAnimation : public WallAnimation
{
public:
    WallNoAnimation() : WallAnimation(0) {}
    ~WallNoAnimation(){}
    void update(double time){}
    bool isComplete(){ return false; }
    AnimationType after(){ return NoAnimation; }

    void renderOn(SDL_Renderer* renderer, ZeroCalculator& camcalc)
    {
        SDL_Texture* texture = getTexture(renderer);
        if(texture == nullptr) return;

        ScreenPos sp = camcalc.posFromWorld(getPosition());

        SDL_Rect dst_rect;
        dst_rect.x = sp.x();
        dst_rect.y = sp.y();
        dst_rect.w = camcalc.wFromWorld(1);
        dst_rect.h = camcalc.hFromWorld(1);

        if(isInFrame(dst_rect,camcalc.getWindowWidth(), camcalc.getWindowHeight()))
        {

            SDL_RenderCopyEx(renderer,
                            texture,
                            src_rect,
                            &dst_rect,
                            getTheta(),
                            nullptr, SDL_FLIP_NONE);
        }
    }
    SDL_Rect* src_rect = nullptr;
};

UniqueAnimation createWallAnimation(AnimationType animation)
{
    switch (animation) {
    case NoAnimation:
        return UniqueAnimation(new WallNoAnimation());
    default:
        return UniqueAnimation(new WallNoAnimation());
    }
}

} // end GraphicsInterface

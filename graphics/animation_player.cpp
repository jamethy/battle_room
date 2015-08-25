#include "animation_player.h"
#include <iostream>

namespace GraphicsInterface
{

PlayerAnimation::PlayerAnimation(double duration) : SDLAnimationClass(duration)
{
}

PlayerAnimation::~PlayerAnimation(){}

UniqueTexture PlayerAnimation::PlayerTexture = UniqueTexture(nullptr);


SDL_Texture* PlayerAnimation::getTexture(SDL_Renderer* renderer)
{
    if(PlayerAnimation::PlayerTexture == nullptr)
    {
        std::string filename = getResourcePath() + "initialcharacter.png";
        PlayerAnimation::PlayerTexture = UniqueTexture(IMG_LoadTexture(renderer,filename.c_str()),SDL_Deleter());
        if(PlayerAnimation::PlayerTexture.get() == nullptr)
        {
            std::cerr << "Failed to load player texture.\n";
        }
    }
    return PlayerAnimation::PlayerTexture.get();
}


class PlayerNoAnimation : public PlayerAnimation
{
public:
    PlayerNoAnimation() : PlayerAnimation(0) {}
    ~PlayerNoAnimation(){}
    void update(double time){}
    bool isComplete(){ return false; }
    AnimationType after(){ return NoAnimation; }

    void renderOn(SDL_Renderer* renderer, CameraClass& cam)
    {
        ScreenPos sp = cam.posFromWorld(getPosition());

        SDL_Rect dst_rect;
        dst_rect.x = sp.x();
        dst_rect.y = sp.y();
        dst_rect.w = cam.wFromWorld(0.05);
        dst_rect.h = cam.hFromWorld(0.05);


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

UniqueAnimation createPlayerAnimation(AnimationType animation)
{
    switch (animation) {
    case NoAnimation:
        return UniqueAnimation(new PlayerNoAnimation());
    default:
        return UniqueAnimation(new PlayerNoAnimation());
    }
}

} // end GraphicsInterface

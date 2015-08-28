#include "animation_player.h"
#include <iostream>

namespace GraphicsInterface
{

PlayerAnimation::PlayerAnimation(double duration) : SDLAnimationClass(duration)
{
}

PlayerAnimation::~PlayerAnimation(){}

TextureMap PlayerAnimation::textureMap = TextureMap();


SDL_Texture* PlayerAnimation::getTexture(SDL_Renderer* renderer)
{
    UniqueTexture& texture = PlayerAnimation::textureMap[renderer];
    if(texture.get() == nullptr)
    {
        texture = loadUniqueTexture(renderer, "initialcharacter.png");

        if(texture.get() == nullptr)
        {
            std::cerr << "Failed to load player texture.\n";
        }
    }
    return texture.get();
}


class PlayerNoAnimation : public PlayerAnimation
{
public:
    PlayerNoAnimation() : PlayerAnimation(0) {}
    ~PlayerNoAnimation(){}
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

        SDL_RenderCopyEx(renderer,
                        texture,
                        src_rect,
                        &dst_rect,
                        getTheta(),
                        nullptr, SDL_FLIP_NONE);
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

#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "sdl_animations.h"

namespace GraphicsInterface
{

class PlayerAnimation : public SDLAnimationClass
{
public:
    PlayerAnimation(double duration);
    virtual ~PlayerAnimation();

    SDL_Texture* getTexture(SDL_Renderer* renderer);
    static TextureMap textureMap;
};


UniqueAnimation createPlayerAnimation(AnimationType animation);

} // end GraphicsInterface
#endif // PLAYER_OBJECT_H

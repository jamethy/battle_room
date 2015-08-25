#ifndef STAR_OBJECT_H
#define STAR_OBJECT_H

#include "sdl_animations.h"

namespace GraphicsInterface
{

class StarAnimation : public SDLAnimationClass
{
public:
    StarAnimation(double duration);
    virtual ~StarAnimation();

    SDL_Texture* getTexture(SDL_Renderer* renderer);
    static UniqueTexture StarTexture;
};


UniqueAnimation createStarAnimation(AnimationType animation);

} // end GraphicsInterface
#endif // STAR_OBJECT_H

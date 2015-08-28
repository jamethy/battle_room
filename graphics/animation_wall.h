#ifndef WALL_OBJECT_H
#define WALL_OBJECT_H

#include "sdl_animations.h"

namespace GraphicsInterface
{

class WallAnimation : public SDLAnimationClass
{
public:
    WallAnimation(double duration);
    virtual ~WallAnimation();

    SDL_Texture* getTexture(SDL_Renderer* renderer);
    static TextureMap textureMap;
};


UniqueAnimation createWallAnimation(AnimationType animation);

} // end GraphicsInterface
#endif // WALL_OBJECT_H

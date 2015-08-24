#ifndef SDL_ANIMATIONS_H
#define SDL_ANIMATIONS_H

#include "../interfaces/graphics_interface.h"
#include "../graphics/graphics_layer.h"
#include "../graphics/camera.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"

namespace GraphicsInterface {


struct SDL_Deleter
{
  void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
  void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
  void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
};

typedef std::unique_ptr<SDL_Window,SDL_Deleter> UniqueWindow;
typedef std::unique_ptr<SDL_Texture,SDL_Deleter> UniqueTexture;
typedef std::unique_ptr<SDL_Renderer,SDL_Deleter> UniqueRenderer;


class SDLAnimationClass : public AnimationBaseClass
{
public:
    SDLAnimationClass(double duration);
    SDLAnimationClass(){}
    virtual ~SDLAnimationClass(){}

    virtual void renderOn(SDL_Renderer* renderer, CameraClass& cam) = 0;

    // Time update functions
    virtual void update(double time) = 0;
    virtual bool isComplete() = 0;
    virtual AnimationType after() = 0;
    virtual void setPlayerPos(Utility::vec2d& pos, double th);
    Utility::vec2d& getPlayerPos();
    double getPlayerTh();

private:
    double m_duration;
    double m_starttime;
    Utility::vec2d m_playerPos;
    double m_playerTh;
};

} // GraphicsInterface namespace
#endif // SDL_ANIMATIONS_H

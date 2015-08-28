#ifndef SDL_ANIMATIONS_H
#define SDL_ANIMATIONS_H

#include "../interfaces/graphics_interface.h"
#include "../graphics/graphics_layer.h"
#include "../graphics/camera.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"

#include <map>

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
typedef std::map<SDL_Renderer*,UniqueTexture> TextureMap;


class SDLAnimationClass : public AnimationBaseClass
{
public:
    SDLAnimationClass(double duration);
    SDLAnimationClass(){}
    virtual ~SDLAnimationClass(){}

    virtual void renderOn(SDL_Renderer* renderer, ZeroCalculator& camcalc) = 0;

    // Time update functions
    virtual void update(double time) = 0;
    virtual bool isComplete() = 0;
    virtual AnimationType after() = 0;
    virtual void setPosition(Utility::vec2d& pos, double th);
    Utility::vec2d& getPosition();
    double getTheta();

private:
    double m_starttime;
    double m_duration;
    Utility::vec2d m_position;
    double m_th;
};


std::string getResourcePath(const std::string &subDir = "");
UniqueTexture loadUniqueTexture(SDL_Renderer* renderer, std::string str);
bool isInFrame(SDL_Rect& rect, int window_width, int window_height);

} // GraphicsInterface namespace
#endif // SDL_ANIMATIONS_H

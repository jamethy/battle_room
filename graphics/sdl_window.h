#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include "../interfaces/graphics_interface.h"
#include "../graphics/sdl_animations.h"
#include "../graphics/camera.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"

#include <vector>

namespace GraphicsInterface
{

class SDLWindowClass : public GraphicsWindowClass
{
public:
    SDLWindowClass(unsigned width, unsigned height);
    ~SDLWindowClass();
    void setViewBounds(Utility::vec2d& worldMin, Utility::vec2d& worldMax);
    void update();

private:

    void draw_object(GraphicsLayer &obj, double drawTime);

    void checkWindowSize();

    UniqueWindow m_window;
    UniqueRenderer m_renderer;
    CameraClass m_camera;
};

}

#endif // SDL_WINDOW_H

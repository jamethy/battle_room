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

    void update(const double& gameTime);

    void setViewBounds(Utility::vec2d& worldMin, Utility::vec2d& worldMax);
    CameraObjectClas* getCamera();

    ~SDLWindowClass();

private:

    void draw_object(GraphicsLayer &obj, double drawTime);

    void checkWindowSize();

    UniqueWindow m_window;
    UniqueRenderer m_renderer;
    CameraClass m_camera;

    static int sdl_window_count;
};

}

#endif // SDL_WINDOW_H

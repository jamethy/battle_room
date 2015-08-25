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
    void update();

private:

    void draw_object(GraphicsLayer &obj);

    double getDrawTime();
    void updateDrawTime();
    double m_drawTime;


    UniqueWindow m_window;
    UniqueRenderer m_renderer;
    CameraClass cam;

    std::vector<UniqueTexture> m_textures;
};

}

#endif // SDL_WINDOW_H

#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include "../interfaces/graphics_interface.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"

namespace GraphicsInterface
{


class SDLWindowClass : public GraphicsWindowClass
{
public:
    SDLWindowClass(unsigned width, unsigned height);
    ~SDLWindowClass();
    void update();

private:

    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
};


}

#endif // SDL_WINDOW_H

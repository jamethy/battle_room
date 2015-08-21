
#include "../interfaces/graphics_interface.h"

#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"

#include <iostream>
#include <exception>

namespace GraphicsInterface {

class GraphicsWindow
{
public:
    GraphicsWindow()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
            std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
            throw std::exception;
        }

        if (TTF_Init() != 0){
            std::cerr << "TTF_Init error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            throw std::exception;
        }

        m_window = SDL_CreateWindow("deathblade_floating", 0, 0, 500,500, SDL_WINDOW_SHOWN);
        if (window == nullptr){
            std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            throw std::exception;
        }

        m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (m_renderer == nullptr){
            std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            throw std::exception;
        }

    }

    ~GraphicsWindow()
    {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }


    void update()
    {

    }

private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
};

}

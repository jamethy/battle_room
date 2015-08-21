#include "sdl_window.h"
#include "object_handler.h"

#include <iostream>
#include <memory>
#include <exception>

namespace GraphicsInterface {

GraphicsWindowClass::~GraphicsWindowClass(){}

UniqueGraphicsWindow createWindow(unsigned width, unsigned height)
{
    try
    {
        return UniqueGraphicsWindow(new SDLWindowClass(width,height));
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}

SDLWindowClass::SDLWindowClass(unsigned width, unsigned height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        throw std::exception();
    }

    if (TTF_Init() != 0){
        std::cerr << "TTF_Init error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::exception();
    }

    m_window = SDL_CreateWindow("deathblade_floating", 0, 0, width, height, SDL_WINDOW_SHOWN);
    if (m_window == nullptr){
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::exception();
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr){
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        throw std::exception();
    }
}

SDLWindowClass::~SDLWindowClass()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void SDLWindowClass::update()
{
    ObjectHandlerClass* objs = ObjectHandlerClass::Instance();
    objs->update();

}



}

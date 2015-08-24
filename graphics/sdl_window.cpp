#include "sdl_window.h"
#include "sdl_animations.h"
#include "object_handler.h"
#include "graphics_layer.h"
#include "../utility/br_time.h"

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

    m_window = UniqueWindow(SDL_CreateWindow("deathblade_floating", 0, 0, width, height, SDL_WINDOW_SHOWN),SDL_Deleter());
    if (m_window == nullptr){
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::exception();
    }

    m_renderer = UniqueRenderer(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED),SDL_Deleter());
    if (m_renderer == nullptr){
        std::cerr << "SDL_CreateRenderer error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::exception();
    }
}

SDLWindowClass::~SDLWindowClass()
{
    SDL_Quit();
}

void SDLWindowClass::update()
{
    updateDrawTime();

    ObjectHandlerClass* objs = ObjectHandlerClass::Instance();
    objs->update();


    SDL_SetRenderDrawColor(m_renderer.get(), 0,0,0,255);
    SDL_RenderClear(m_renderer.get());

    for (DrawableObjectClass* obj : *objs)
    {

    }


    SDL_RenderPresent(m_renderer.get());

}

void SDLWindowClass::draw_object(GraphicsLayer &obj)
{
    SDLAnimationClass* animation = (SDLAnimationClass*)obj.getAnimation(getDrawTime());
    animation->renderOn(m_renderer.get(), cam);
}

double SDLWindowClass::getDrawTime()
{
    return m_drawTime;
}

void SDLWindowClass::updateDrawTime()
{
    m_drawTime = Utility::TimeBase::getTime();
}



}
